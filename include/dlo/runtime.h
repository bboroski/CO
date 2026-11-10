#ifndef DLO_RUNTIME_H
#define DLO_RUNTIME_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t dlo_result_t;

enum {
    DLO_OK      =  0,
    DLO_EINVAL  = -1,
    DLO_ESTATE  = -2,
    DLO_EBUSY   = -3,
    DLO_EIO     = -4
};

typedef enum {
    DLO_STATE_STOPPED = 0,
    DLO_STATE_STARTING,
    DLO_STATE_RUNNING,
    DLO_STATE_STEPPING,
    DLO_STATE_FAULTED,
    DLO_STATE_STOPPING
} dlo_state_t;

typedef dlo_result_t (*dlo_init_fn)(void *context);
typedef dlo_result_t (*dlo_step_fn)(void *context);
typedef void (*dlo_shutdown_fn)(void *context);

typedef struct {
    void *context;
    dlo_init_fn init;
    dlo_step_fn step;
    dlo_shutdown_fn shutdown;
} dlo_hooks_t;

typedef struct {
    dlo_hooks_t hooks;
    dlo_state_t state;
    dlo_result_t last_result;
    uint32_t cycle_count;
    uint8_t cleanup_required;
} dlo_runtime_t;

/* Copies callback bindings. No allocation is performed. */
dlo_result_t dlo_runtime_init(dlo_runtime_t *runtime, const dlo_hooks_t *hooks);
/* Valid only from STOPPED. Failed init leaves FAULTED and requires stop. */
dlo_result_t dlo_runtime_start(dlo_runtime_t *runtime);
/* Executes one step callback; recursive poll/stop calls are rejected. */
dlo_result_t dlo_runtime_poll(dlo_runtime_t *runtime);
/* Performs cleanup at most once; safe to call repeatedly after STOPPED. */
dlo_result_t dlo_runtime_stop(dlo_runtime_t *runtime);

dlo_state_t dlo_runtime_state(const dlo_runtime_t *runtime);
dlo_result_t dlo_runtime_last_result(const dlo_runtime_t *runtime);
uint32_t dlo_runtime_cycle_count(const dlo_runtime_t *runtime);

#ifdef __cplusplus
}
#endif

#endif
