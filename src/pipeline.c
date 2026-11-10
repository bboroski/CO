#include "co/pipeline.h"

#include <limits.h>
#include <stddef.h>

static void co_pipeline_increment_sequence(co_pipeline_t *pipeline)
{
    if (pipeline->transition_sequence < UINT32_MAX) {
        pipeline->transition_sequence++;
    }
}

co_result_t co_pipeline_init(co_pipeline_t *pipeline,
                             const co_stage_t *stages,
                             uint32_t stage_count)
{
    uint32_t index;

    if (pipeline == NULL || stages == NULL || stage_count == 0U ||
        stage_count > CO_PIPELINE_MAX_STAGES) {
        return CO_EINVAL;
    }
    for (index = 0U; index < stage_count; ++index) {
        if (stages[index].execute == NULL) {
            return CO_EINVAL;
        }
    }

    pipeline->stages = stages;
    pipeline->stage_count = stage_count;
    pipeline->current_stage = 0U;
    pipeline->transition_sequence = 0U;
    pipeline->state = CO_PIPELINE_RUNNING;
    pipeline->last_result = CO_OK;
    return CO_OK;
}

co_result_t co_pipeline_step(co_pipeline_t *pipeline)
{
    co_result_t result;

    if (pipeline == NULL) {
        return CO_EINVAL;
    }
    if (pipeline->state != CO_PIPELINE_RUNNING ||
        pipeline->current_stage >= pipeline->stage_count) {
        return CO_ESTATE;
    }

    result = pipeline->stages[pipeline->current_stage].execute(
        pipeline->stages[pipeline->current_stage].context);
    co_pipeline_increment_sequence(pipeline);
    pipeline->last_result = result;
    if (result != CO_OK) {
        pipeline->state = CO_PIPELINE_FAULTED;
        return result;
    }

    pipeline->current_stage++;
    if (pipeline->current_stage == pipeline->stage_count) {
        pipeline->state = CO_PIPELINE_COMPLETE;
    }
    return CO_OK;
}

co_result_t co_pipeline_run(co_pipeline_t *pipeline,
                            uint32_t stage_budget,
                            uint32_t *stages_executed_out)
{
    uint32_t executed = 0U;
    co_result_t result;

    if (pipeline == NULL || stages_executed_out == NULL || stage_budget == 0U) {
        return CO_EINVAL;
    }
    while (executed < stage_budget && pipeline->state == CO_PIPELINE_RUNNING) {
        result = co_pipeline_step(pipeline);
        executed++;
        if (result != CO_OK) {
            *stages_executed_out = executed;
            return result;
        }
    }
    *stages_executed_out = executed;
    if (pipeline->state == CO_PIPELINE_COMPLETE) {
        return CO_OK;
    }
    if (pipeline->state == CO_PIPELINE_FAULTED) {
        return pipeline->last_result;
    }
    return CO_EBUSY;
}
