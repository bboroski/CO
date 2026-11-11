#ifndef CO_DIAGNOSTICS_H
#define CO_DIAGNOSTICS_H
#include "co/runtime.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    const char *state_key;
    const char *next_action_key;
    uint32_t cycle_count;
    co_result_t last_result;
    uint8_t cleanup_required;
    uint8_t can_poll;
    uint8_t can_stop;
} co_runtime_diagnostics_t;
/* Read-only snapshot with a localization-ready next-action key. */
co_result_t co_runtime_diagnostics(const co_runtime_t *runtime,
                                   co_runtime_diagnostics_t *out);
#ifdef __cplusplus
}
#endif
#endif
