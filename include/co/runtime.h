#ifndef CO_RUNTIME_H
#define CO_RUNTIME_H
/* Source-compatibility facade. New code should include dlo/runtime.h. */
#include "dlo/runtime.h"

typedef dlo_result_t co_result_t;
#define CO_OK DLO_OK
#define CO_EINVAL DLO_EINVAL
#define CO_ESTATE DLO_ESTATE
#define CO_EBUSY DLO_EBUSY
#define CO_EIO DLO_EIO

typedef dlo_state_t co_state_t;
#define CO_STATE_STOPPED DLO_STATE_STOPPED
#define CO_STATE_STARTING DLO_STATE_STARTING
#define CO_STATE_RUNNING DLO_STATE_RUNNING
#define CO_STATE_STEPPING DLO_STATE_STEPPING
#define CO_STATE_FAULTED DLO_STATE_FAULTED
#define CO_STATE_STOPPING DLO_STATE_STOPPING

typedef dlo_init_fn co_init_fn;
typedef dlo_step_fn co_step_fn;
typedef dlo_shutdown_fn co_shutdown_fn;
typedef dlo_hooks_t co_hooks_t;
typedef dlo_runtime_t co_runtime_t;

#define co_runtime_init dlo_runtime_init
#define co_runtime_start dlo_runtime_start
#define co_runtime_poll dlo_runtime_poll
#define co_runtime_stop dlo_runtime_stop
#define co_runtime_state dlo_runtime_state
#define co_runtime_last_result dlo_runtime_last_result
#define co_runtime_cycle_count dlo_runtime_cycle_count

#endif
