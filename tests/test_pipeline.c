#include "co/pipeline.h"

#include <assert.h>
#include <stdio.h>

typedef struct { int value; int calls; } stage_context_t;

static co_result_t increment(void *raw)
{
    stage_context_t *context = (stage_context_t *)raw;
    context->value++;
    context->calls++;
    return CO_OK;
}

static co_result_t fail_stage(void *raw)
{
    stage_context_t *context = (stage_context_t *)raw;
    context->calls++;
    return CO_EIO;
}

int main(void)
{
    stage_context_t a = {0, 0}, b = {0, 0}, c = {0, 0};
    const co_stage_t stages[] = {
        {"prepare", increment, &a}, {"validate", increment, &b},
        {"publish", increment, &c}
    };
    const co_stage_t failing[] = {
        {"prepare", increment, &a}, {"fault", fail_stage, &b},
        {"never-run", increment, &c}
    };
    co_pipeline_t pipeline;
    uint32_t executed = 0U;

    assert(co_pipeline_init(&pipeline, stages, 3U) == CO_OK);
    assert(co_pipeline_run(&pipeline, 2U, &executed) == CO_EBUSY);
    assert(executed == 2U && pipeline.current_stage == 2U);
    assert(co_pipeline_run(&pipeline, 2U, &executed) == CO_OK);
    assert(executed == 1U && pipeline.state == CO_PIPELINE_COMPLETE);
    assert(pipeline.transition_sequence == 3U);
    assert(a.calls == 1 && b.calls == 1 && c.calls == 1);
    assert(co_pipeline_step(&pipeline) == CO_ESTATE);

    assert(co_pipeline_init(&pipeline, failing, 3U) == CO_OK);
    assert(co_pipeline_run(&pipeline, 3U, &executed) == CO_EIO);
    assert(executed == 2U && pipeline.state == CO_PIPELINE_FAULTED);
    assert(c.calls == 1);
    assert(co_pipeline_run(&pipeline, 3U, &executed) == CO_EIO);
    assert(executed == 0U);

    assert(co_pipeline_init(&pipeline, stages, CO_PIPELINE_MAX_STAGES + 1U) == CO_EINVAL);
    puts("CO pipeline tests: PASS");
    return 0;
}
