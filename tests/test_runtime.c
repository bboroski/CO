#include "dlo/runtime.h

#include <assert.h>
#include <stdio.h>

typedef struct {
    unsigned init_calls;
    unsigned step_calls;
    unsigned shutdown_calls;
    int fail_init;
    int fail_step;
    dlo_result_t recursive_poll_result;
    dlo_runtime_t *runtime;
} test_context_t;

static dlo_result_t test_init(void *context)
{
    test_context_t *test = (test_context_t *)context;
    test->init_calls++;
    return (test->fail_init != 0) ? DLO_EIO : DLO_OK;
}

static dlo_result_t test_step(void *context)
{
    test_context_t *test = (test_context_t *)context;
    test->step_calls++;
    if (test->runtime != NULL) {
        test->recursive_poll_result = dlo_runtime_poll(test->runtime);
    }
    return (test->fail_step != 0) ? DLO_EIO : DLO_OK;
}

static void test_shutdown(void *context)
{
    test_context_t *test = (test_context_t *)context;
    test->shutdown_calls++;
}

int main(void)
{
    test_context_t context = {0U, 0U, 0U, 0, 0, DLO_OK, NULL};
    dlo_hooks_t hooks = {&context, test_init, test_step, test_shutdown};
    dlo_runtime_t runtime;

    assert(dlo_runtime_init(&runtime, &hooks) == DLO_OK);
    context.runtime = &runtime;
    assert(dlo_runtime_state(&runtime) == DLO_STATE_STOPPED);
    assert(dlo_runtime_start(&runtime) == DLO_OK);
    assert(dlo_runtime_start(&runtime) == DLO_ESTATE);
    assert(dlo_runtime_state(&runtime) == DLO_STATE_RUNNING);

    assert(dlo_runtime_poll(&runtime) == DLO_OK);
    assert(context.recursive_poll_result == DLO_ESTATE);
    context.fail_step = 1;
    assert(dlo_runtime_poll(&runtime) == DLO_EIO);
    assert(context.recursive_poll_result == DLO_ESTATE);
    assert(dlo_runtime_state(&runtime) == DLO_STATE_FAULTED);
    assert(dlo_runtime_last_result(&runtime) == DLO_EIO);
    assert(dlo_runtime_cycle_count(&runtime) == 2U);

    assert(dlo_runtime_stop(&runtime) == DLO_OK);
    assert(dlo_runtime_stop(&runtime) == DLO_OK);
    assert(dlo_runtime_state(&runtime) == DLO_STATE_STOPPED);
    assert(context.init_calls == 1U);
    assert(context.step_calls == 2U);
    assert(context.shutdown_calls == 1U);

    /* Failed init still requires one cleanup call for partially acquired state. */
    {
        test_context_t failed = {0U, 0U, 0U, 1, 0, DLO_OK, NULL};
        dlo_hooks_t failed_hooks = {&failed, test_init, test_step, test_shutdown};
        dlo_runtime_t failed_runtime;

        assert(dlo_runtime_init(&failed_runtime, &failed_hooks) == DLO_OK);
        assert(dlo_runtime_start(&failed_runtime) == DLO_EIO);
        assert(dlo_runtime_state(&failed_runtime) == DLO_STATE_FAULTED);
        assert(dlo_runtime_poll(&failed_runtime) == DLO_ESTATE);
        assert(dlo_runtime_stop(&failed_runtime) == DLO_OK);
        assert(failed.init_calls == 1U);
        assert(failed.step_calls == 0U);
        assert(failed.shutdown_calls == 1U);
        assert(dlo_runtime_state(&failed_runtime) == DLO_STATE_STOPPED);
    }

    puts("CO runtime tests: PASS");
    return 0;
}
