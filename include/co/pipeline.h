#ifndef CO_PIPELINE_H
#define CO_PIPELINE_H

#include "co/runtime.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CO_PIPELINE_MAX_STAGES 16U

typedef co_result_t (*co_stage_fn)(void *context);

typedef struct {
    const char *name;
    co_stage_fn execute;
    void *context;
} co_stage_t;

typedef enum {
    CO_PIPELINE_IDLE = 0,
    CO_PIPELINE_RUNNING,
    CO_PIPELINE_COMPLETE,
    CO_PIPELINE_FAULTED
} co_pipeline_state_t;

typedef struct {
    const co_stage_t *stages; /* caller-owned; must outlive the pipeline */
    uint32_t stage_count;
    uint32_t current_stage;
    uint32_t transition_sequence;
    co_pipeline_state_t state;
    co_result_t last_result;
} co_pipeline_t;

/* Binds a bounded, ordered stage list without allocation. */
co_result_t co_pipeline_init(co_pipeline_t *pipeline,
                             const co_stage_t *stages,
                             uint32_t stage_count);

/* Executes exactly one stage. A failed stage faults the pipeline immediately. */
co_result_t co_pipeline_step(co_pipeline_t *pipeline);

/* Executes at most stage_budget stages; returns CO_EBUSY when work remains. */
co_result_t co_pipeline_run(co_pipeline_t *pipeline,
                            uint32_t stage_budget,
                            uint32_t *stages_executed_out);

#ifdef __cplusplus
}
#endif

#endif
