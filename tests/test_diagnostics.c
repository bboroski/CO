#include "co/diagnostics.h"
#include <assert.h>
#include <string.h>
static co_result_t init_ok(void *p) { (void)p; return CO_OK; }
static co_result_t step_ok(void *p) { (void)p; return CO_OK; }
static void stop_noop(void *p) { (void)p; }
int main(void)
{
    co_runtime_t runtime;
    co_runtime_diagnostics_t d;
    co_hooks_t hooks = {0, init_ok, step_ok, stop_noop};
    assert(co_runtime_diagnostics(0, &d) == CO_EINVAL);
    assert(co_runtime_init(&runtime, &hooks) == CO_OK);
    assert(co_runtime_diagnostics(&runtime, &d) == CO_OK);
    assert(strcmp(d.state_key, "stopped") == 0 && d.can_poll == 0u);
    assert(co_runtime_start(&runtime) == CO_OK);
    assert(co_runtime_diagnostics(&runtime, &d) == CO_OK);
    assert(strcmp(d.state_key, "running") == 0 && d.can_poll == 1u);
    assert(co_runtime_poll(&runtime) == CO_OK);
    assert(co_runtime_diagnostics(&runtime, &d) == CO_OK && d.cycle_count == 1u);
    runtime.state = CO_STATE_FAULTED;
    runtime.last_result = CO_EIO;
    runtime.cleanup_required = 1u;
    assert(co_runtime_diagnostics(&runtime, &d) == CO_OK);
    assert(strcmp(d.next_action_key, "inspect_last_result_then_stop_for_cleanup") == 0);
    assert(d.can_stop == 1u && d.cleanup_required == 1u);
    runtime.state = (co_state_t)99;
    assert(co_runtime_diagnostics(&runtime, &d) == CO_ESTATE);
    return 0;
}
