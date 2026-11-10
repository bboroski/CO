#ifndef CO_SAINTSI_BRIDGE_H
#define CO_SAINTSI_BRIDGE_H

/* Optional observer bridge; compile the consumer with both include roots. */
#include "co/runtime.h"
#include "saintsi/health.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CO_SAINTSI_SKIPPED_NOT_RUNNING INT32_C(1)

/* Register one CO runtime as a monitored component before entering its loop. */
static inline saintsi_result_t co_saintsi_register_runtime(
    saintsi_supervisor_t *supervisor,
    uint32_t component_id,
    uint32_t timeout_ticks,
    uint32_t now_ticks)
{
    return saintsi_register_component(
        supervisor, component_id, timeout_ticks, now_ticks);
}

/*
 * Call after a completed poll. A non-running (including FAULTED) runtime
 * deliberately does not refresh its heartbeat; SaintSI can then report it
 * stale on the next health check. This helper never performs recovery.
 */
static inline int32_t co_saintsi_refresh_runtime(
    const co_runtime_t *runtime,
    saintsi_supervisor_t *supervisor,
    uint32_t component_id,
    uint32_t now_ticks)
{
    if (runtime == 0 || supervisor == 0) {
        return CO_EINVAL;
    }
    if (co_runtime_state(runtime) != CO_STATE_RUNNING) {
        return CO_SAINTSI_SKIPPED_NOT_RUNNING;
    }
    return (int32_t)saintsi_heartbeat(supervisor, component_id, now_ticks);
}

#ifdef __cplusplus
}
#endif
#endif
