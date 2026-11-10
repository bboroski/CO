#ifndef CO_RUNTIME_H
#define CO_RUNTIME_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t co_result_t;

enum {
    CO_OK      =  0,
    CO_EINVAL  = -1,
    CO_ESTATE  = -2,
    CO_EBUSY   = -3,
    CO_EIO     = -4
};

typedef enum {
    CO_STATE_STOPPED = 0,
    CO_STATE_STARTING,
    CO_STATE_RUNNING,
    CO_STATE_FAULTED,
    CO_STATE_STOPPING
} co_state_t;

typedef co_result_t (*co_init_fn)(void *context);
typedef co_result_t (*co_step_fn)(void *context);
typedef void (*co_shutdown_fn)(void *context);

typedef struct {
    void *context;
    co_init_fn init;
    co_step_fn step;
    co_shutdown_fn shutdown;
} co_hooks_t;

typedef struct {
    co_hooks_t hooks;
    co_state_t state;
    co_result_t last_result;
    uint32_t cycle_count;
    uint8_t cleanup_required;
} co_runtime_t;

/* Copies callback bindings. No allocation is performed. */
co_result_t co_runtime_init(co_runtime_t *runtime, const co_hooks_t *hooks);

/* Valid only from STOPPED. Failed init leaves FAULTED and still requires stop. */
co_result_t co_runtime_start(co_runtime_t *runtime);

/* Executes one step callback. A nonzero callback result faults the runtime. */
co_result_t co_runtime_poll(co_runtime_t *runtime);

/* Performs cleanup at most once; safe to call repeatedly after STOPPED. */
co_result_t co_runtime_stop(co_runtime_t *runtime);

co_state_t co_runtime_state(const co_runtime_t *runtime);
co_result_t co_runtime_last_result(const co_runtime_t *runtime);
uint32_t co_runtime_cycle_count(const co_runtime_t *runtime);

#ifdef __cplusplus
}
#endif

#endif
