#include "dlo/runtime.h"

#include <limits.h>
#include <stddef.h>

dlo_result_t dlo_runtime_init(dlo_runtime_t *runtime, const dlo_hooks_t *hooks)
{
    if (runtime == NULL || hooks == NULL ||
        hooks->init == NULL || hooks->step == NULL) {
        return DLO_EINVAL;
    }

    runtime->hooks = *hooks;
    runtime->state = DLO_STATE_STOPPED;
    runtime->last_result = DLO_OK;
    runtime->cycle_count = 0U;
    runtime->cleanup_required = 0U;
    return DLO_OK;
}

dlo_result_t dlo_runtime_start(dlo_runtime_t *runtime)
{
    dlo_result_t result;

    if (runtime == NULL) {
        return DLO_EINVAL;
    }
    if (runtime->state != DLO_STATE_STOPPED) {
        return DLO_ESTATE;
    }

    runtime->state = DLO_STATE_STARTING;
    runtime->last_result = DLO_OK;
    runtime->cleanup_required = 1U;

    result = runtime->hooks.init(runtime->hooks.context);
    if (result != DLO_OK) {
        runtime->last_result = result;
        runtime->state = DLO_STATE_FAULTED;
        return result;
    }

    runtime->state = DLO_STATE_RUNNING;
    return DLO_OK;
}

dlo_result_t dlo_runtime_poll(dlo_runtime_t *runtime)
{
    dlo_result_t result;

    if (runtime == NULL) {
        return DLO_EINVAL;
    }
    if (runtime->state != DLO_STATE_RUNNING) {
        return DLO_ESTATE;
    }

    runtime->state = DLO_STATE_STEPPING;
    result = runtime->hooks.step(runtime->hooks.context);
    if (runtime->cycle_count < UINT32_MAX) {
        runtime->cycle_count++;
    }

    if (result != DLO_OK) {
        runtime->last_result = result;
        runtime->state = DLO_STATE_FAULTED;
        return result;
    }

    runtime->state = DLO_STATE_RUNNING;
    return DLO_OK;
}

dlo_result_t dlo_runtime_stop(dlo_runtime_t *runtime)
{
    if (runtime == NULL) {
        return DLO_EINVAL;
    }
    if (runtime->state == DLO_STATE_STOPPED) {
        return DLO_OK;
    }
    if (runtime->state == DLO_STATE_STARTING ||
        runtime->state == DLO_STATE_STEPPING ||
        runtime->state == DLO_STATE_STOPPING) {
        return DLO_EBUSY;
    }

    runtime->state = DLO_STATE_STOPPING;
    if (runtime->cleanup_required != 0U) {
        runtime->cleanup_required = 0U;
        if (runtime->hooks.shutdown != NULL) {
            runtime->hooks.shutdown(runtime->hooks.context);
        }
    }

    runtime->state = DLO_STATE_STOPPED;
    return DLO_OK;
}

dlo_state_t dlo_runtime_state(const dlo_runtime_t *runtime)
{
    return (runtime == NULL) ? DLO_STATE_FAULTED : runtime->state;
}

dlo_result_t dlo_runtime_last_result(const dlo_runtime_t *runtime)
{
    return (runtime == NULL) ? DLO_EINVAL : runtime->last_result;
}

uint32_t dlo_runtime_cycle_count(const dlo_runtime_t *runtime)
{
    return (runtime == NULL) ? 0U : runtime->cycle_count;
}
