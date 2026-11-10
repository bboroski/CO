#include "co/runtime.h"

#include <assert.h>
#include <stdio.h>

typedef struct {
    unsigned init_calls;
    unsigned step_calls;
    unsigned shutdown_calls;
    int fail_step;
    co_result_t recursive_poll_result;
    co_runtime_t *runtime;
} test_context_t;

static co_result_t test_init(void *context)
{
    test_context_t *test = (test_context_t *)context;
    test->init_calls++;
    return CO_OK;
}

static co_result_t test_step(void *context)
{
    test_context_t *test = (test_context_t *)context;
    test->step_calls++;
    if (test->runtime != NULL) {
        test->recursive_poll_result = co_runtime_poll(test->runtime);
    }
    return (test->fail_step != 0) ? CO_EIO : CO_OK;
}

static void test_shutdown(void *context)
{
    test_context_t *test = (test_context_t *)context;
    test->shutdown_calls++;
}

int main(void)
{
    test_context_t context = {0U, 0U, 0U, 0, CO_OK, NULL};
    co_hooks_t hooks = {&context, test_init, test_step, test_shutdown};
    co_runtime_t runtime;

    assert(co_runtime_init(&runtime, &hooks) == CO_OK);
    context.runtime = &runtime;
    assert(co_runtime_state(&runtime) == CO_STATE_STOPPED);
    assert(co_runtime_start(&runtime) == CO_OK);
    assert(co_runtime_start(&runtime) == CO_ESTATE);
    assert(co_runtime_state(&runtime) == CO_STATE_RUNNING);

    assert(co_runtime_poll(&runtime) == CO_OK);
    assert(context.recursive_poll_result == CO_ESTATE);
    context.fail_step = 1;
    assert(co_runtime_poll(&runtime) == CO_EIO);
    assert(context.recursive_poll_result == CO_ESTATE);
    assert(co_runtime_state(&runtime) == CO_STATE_FAULTED);
    assert(co_runtime_last_result(&runtime) == CO_EIO);
    assert(co_runtime_cycle_count(&runtime) == 2U);

    assert(co_runtime_stop(&runtime) == CO_OK);
    assert(co_runtime_stop(&runtime) == CO_OK);
    assert(co_runtime_state(&runtime) == CO_STATE_STOPPED);
    assert(context.init_calls == 1U);
    assert(context.step_calls == 2U);
    assert(context.shutdown_calls == 1U);

    puts("CO runtime tests: PASS");
    return 0;
}
