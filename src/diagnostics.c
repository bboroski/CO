#include "co/diagnostics.h"

#include <string.h>

co_result_t co_runtime_diagnostics(const co_runtime_t *runtime,
                                   co_runtime_diagnostics_t *out)
{
    if (runtime == NULL || out == NULL) return CO_EINVAL;
    memset(out, 0, sizeof(*out));
    out->cycle_count = runtime->cycle_count;
    out->last_result = runtime->last_result;
    out->cleanup_required = runtime->cleanup_required;
    out->can_stop = (uint8_t)(runtime->state == CO_STATE_RUNNING ||
                              runtime->state == CO_STATE_FAULTED);
    switch (runtime->state) {
    case CO_STATE_STOPPED:
        out->state_key = "stopped";
        out->next_action_key = "start_when_dependencies_are_ready";
        break;
    case CO_STATE_STARTING:
        out->state_key = "starting";
        out->next_action_key = "wait_for_initialization_callback";
        break;
    case CO_STATE_RUNNING:
        out->state_key = "running";
        out->next_action_key = "poll_one_runtime_cycle";
        out->can_poll = 1u;
        break;
    case CO_STATE_STEPPING:
        out->state_key = "stepping";
        out->next_action_key = "wait_for_current_step_to_return";
        break;
    case CO_STATE_FAULTED:
        out->state_key = "faulted";
        out->next_action_key = runtime->cleanup_required
            ? "inspect_last_result_then_stop_for_cleanup"
            : "inspect_last_result_before_restart";
        break;
    case CO_STATE_STOPPING:
        out->state_key = "stopping";
        out->next_action_key = "allow_shutdown_callback_to_finish";
        break;
    default:
        return CO_ESTATE;
    }
    return CO_OK;
}
