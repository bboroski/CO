#ifndef CO_RUNTIME_H
#define CO_RUNTIME_H

/* Compatibility surface. New integrations should include <dclr/runtime.h>. */
#include "dclr/runtime.h"

typedef dclr_result_t co_result_t;
typedef dclr_state_t co_state_t;
typedef dclr_init_fn co_init_fn;
typedef dclr_step_fn co_step_fn;
typedef dclr_shutdown_fn co_shutdown_fn;
typedef dclr_hooks_t co_hooks_t;
typedef dclr_runtime_t co_runtime_t;

#define CO_OK DCLR_OK
#define CO_EINVAL DCLR_EINVAL
#define CO_ESTATE DCLR_ESTATE
#define CO_EBUSY DCLR_EBUSY
#define CO_EIO DCLR_EIO
#define CO_STATE_STOPPED DCLR_STATE_STOPPED
#define CO_STATE_STARTING DCLR_STATE_STARTING
#define CO_STATE_RUNNING DCLR_STATE_RUNNING
#define CO_STATE_STEPPING DCLR_STATE_STEPPING
#define CO_STATE_FAULTED DCLR_STATE_FAULTED
#define CO_STATE_STOPPING DCLR_STATE_STOPPING

#define co_runtime_init dclr_runtime_init
#define co_runtime_start dclr_runtime_start
#define co_runtime_poll dclr_runtime_poll
#define co_runtime_stop dclr_runtime_stop
#define co_runtime_state dclr_runtime_state
#define co_runtime_last_result dclr_runtime_last_result
#define co_runtime_cycle_count dclr_runtime_cycle_count

#endif
