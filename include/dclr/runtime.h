#ifndef DCLR_RUNTIME_H
#define DCLR_RUNTIME_H
/* Source-compatibility facade. New code should include dlo/runtime.h. */
#include "dlo/runtime.h"

typedef dlo_result_t dclr_result_t;
#define DCLR_OK DLO_OK
#define DCLR_EINVAL DLO_EINVAL
#define DCLR_ESTATE DLO_ESTATE
#define DCLR_EBUSY DLO_EBUSY
#define DCLR_EIO DLO_EIO

typedef dlo_state_t dclr_state_t;
#define DCLR_STATE_STOPPED DLO_STATE_STOPPED
#define DCLR_STATE_STARTING DLO_STATE_STARTING
#define DCLR_STATE_RUNNING DLO_STATE_RUNNING
#define DCLR_STATE_STEPPING DLO_STATE_STEPPING
#define DCLR_STATE_FAULTED DLO_STATE_FAULTED
#define DCLR_STATE_STOPPING DLO_STATE_STOPPING

typedef dlo_init_fn dclr_init_fn;
typedef dlo_step_fn dclr_step_fn;
typedef dlo_shutdown_fn dclr_shutdown_fn;
typedef dlo_hooks_t dclr_hooks_t;
typedef dlo_runtime_t dclr_runtime_t;

#define dclr_runtime_init dlo_runtime_init
#define dclr_runtime_start dlo_runtime_start
#define dclr_runtime_poll dlo_runtime_poll
#define dclr_runtime_stop dlo_runtime_stop
#define dclr_runtime_state dlo_runtime_state
#define dclr_runtime_last_result dlo_runtime_last_result
#define dclr_runtime_cycle_count dlo_runtime_cycle_count

#endif
