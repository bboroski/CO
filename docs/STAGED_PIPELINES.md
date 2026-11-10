# CO bounded staged pipelines

CO keeps component lifetime and ordered multi-stage execution separate. The new pipeline API provides deterministic orchestration for short workflows without dynamic allocation.

## Contract

- A pipeline contains 1–16 caller-owned stage descriptors.
- Initialization validates the full stage table before any callback runs.
- `co_pipeline_step` executes exactly one stage in array order.
- `co_pipeline_run` executes no more than the caller's stage budget.
- A callback error moves the pipeline to `FAULTED`; later stages are not invoked.
- `transition_sequence` counts executed stages and saturates instead of wrapping.

The stage array and callback contexts must outlive the pipeline. This API does not roll back external side effects. Callers that need compensation must provide explicit cleanup stages or use the existing runtime shutdown hooks.

## Verification

`make test` covers budget exhaustion, deterministic ordering, completion, failure isolation and rejection of stage lists larger than the fixed capacity.
