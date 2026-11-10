#ifndef DLO_RIAE_BRIDGE_H
#define DLO_RIAE_BRIDGE_H

#include <stdint.h>
#include "dlo/runtime.h"
#include "riae/health.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DLO_RIAE_SKIPPED_NOT_RUNNING INT32_C(1)

/* Register a DLO runtime for observation before entering its execution loop. */
static inline riae_result_t dlo_riae_register_runtime(
    riae_supervisor_t *supervisor,
    uint32_t component_id,
    uint32_t timeout_ticks,
    uint32_t now_ticks)
{
    return riae_register_component(
        supervisor, component_id, timeout_ticks, now_ticks);
}

/*
 * Call only after a completed poll. A non-running runtime deliberately does
 * not refresh its heartbeat. The observer can then report stale progress.
 * This adapter never requests recovery or actuates hardware.
 */
static inline int32_t dlo_riae_refresh_runtime(
    const dlo_runtime_t *runtime,
    riae_supervisor_t *supervisor,
    uint32_t component_id,
    uint32_t now_ticks)
{
    if (runtime == 0 || supervisor == 0) {
        return DLO_EINVAL;
    }
    if (dlo_runtime_state(runtime) != DLO_STATE_RUNNING) {
        return DLO_RIAE_SKIPPED_NOT_RUNNING;
    }
    return (int32_t)riae_heartbeat(supervisor, component_id, now_ticks);
}

#ifdef __cplusplus
}
#endif

#endif
