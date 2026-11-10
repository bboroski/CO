#ifndef CO_SAINTSI_BRIDGE_H
#define CO_SAINTSI_BRIDGE_H

/* Source-compatibility adapter. New code should include <dlo/riae_bridge.h>. */
#include "dlo/riae_bridge.h"
#include "co/runtime.h"
#include "saintsi/health.h"

#define CO_SAINTSI_SKIPPED_NOT_RUNNING DLO_RIAE_SKIPPED_NOT_RUNNING
#define co_saintsi_register_runtime dlo_riae_register_runtime
#define co_saintsi_refresh_runtime dlo_riae_refresh_runtime

#endif
