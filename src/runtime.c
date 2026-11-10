#include "co/runtime.h"

#include <limits.h>
#include <stddef.h>

co_result_t co_runtime_init(co_runtime_t *runtime, const co_hooks_t *hooks)
{
    if (runtime == NULL || hooks == NULL ||
        hooks->init == NULL || hooks->step == NULL) {
        return CO_EINVAL;
    }

    runtime->hooks = *hooks;
    runtime->state = CO_STATE_STOPPED;
    runtime->last_result = CO_OK;
    runtime->cycle_count = 0U;
    runtime->cleanup_required = 0U;
    return CO_OK;
}

co_result_t co_runtime_start(co_runtime_t *runtime)
{
    co_result_t result;

    if (runtime == NULL) {
        return CO_EINVAL;
    }
    if (runtime->state != CO_STATE_STOPPED) {
        return CO_ESTATE;
    }

    runtime->state = CO_STATE_STARTING;
    runtime->last_result = CO_OK;
    runtime->cleanup_required = 1U;

    result = runtime->hooks.init(runtime->hooks.context);
    if (result != CO_OK) {
        runtime->last_result = result;
        runtime->state = CO_STATE_FAULTED;
        return result;
    }

    runtime->state = CO_STATE_RUNNING;
    return CO_OK;
}

co_result_t co_runtime_poll(co_runtime_t *runtime)
{
    co_result_t result;

    if (runtime == NULL) {
        return CO_EINVAL;
    }
    if (runtime->state != CO_STATE_RUNNING) {
        return CO_ESTATE;
    }

    runtime->state = CO_STATE_STEPPING;
    result = runtime->hooks.step(runtime->hooks.context);
    if (runtime->cycle_count < UINT32_MAX) {
        runtime->cycle_count++;
    }

    if (result != CO_OK) {
        runtime->last_result = result;
        runtime->state = CO_STATE_FAULTED;
        return result;
    }

    runtime->state = CO_STATE_RUNNING;
    return CO_OK;
}

co_result_t co_runtime_stop(co_runtime_t *runtime)
{
    if (runtime == NULL) {
        return CO_EINVAL;
    }
    if (runtime->state == CO_STATE_STOPPED) {
        return CO_OK;
    }
    if (runtime->state == CO_STATE_STARTING ||
        runtime->state == CO_STATE_STEPPING ||
        runtime->state == CO_STATE_STOPPING) {
        return CO_EBUSY;
    }

    runtime->state = CO_STATE_STOPPING;
    if (runtime->cleanup_required != 0U) {
        runtime->cleanup_required = 0U;
        if (runtime->hooks.shutdown != NULL) {
            runtime->hooks.shutdown(runtime->hooks.context);
        }
    }

    runtime->state = CO_STATE_STOPPED;
    return CO_OK;
}

co_state_t co_runtime_state(const co_runtime_t *runtime)
{
    return (runtime == NULL) ? CO_STATE_FAULTED : runtime->state;
}

co_result_t co_runtime_last_result(const co_runtime_t *runtime)
{
    return (runtime == NULL) ? CO_EINVAL : runtime->last_result;
}

uint32_t co_runtime_cycle_count(const co_runtime_t *runtime)
{
    return (runtime == NULL) ? 0U : runtime->cycle_count;
}
