# Signal Pipeline Lifecycle

CO can orchestrate a sequence of bounded processing stages without owning text parsing or language semantics. A host application may compose the following callbacks:

```text
STOPPED -> STARTING -> RUNNING
                       |
                       +-> one bounded poll/step
                              |
                              +-> RUNNING on success
                              +-> FAULTED on error
FAULTED -> STOPPING -> STOPPED
```

## Suggested stage order

1. Validate input size, encoding declaration, and caller-owned lifetime.
2. Normalize a working copy according to the selected policy.
3. Run SAMBU script and structure diagnostics.
4. Attach caller-supplied representation hints.
5. Produce a metadata-only envelope.
6. Hand off the report to the explicitly authorized host sink.

Each `co_runtime_poll` executes one application-defined step. The callback must have a finite work bound and return a status. If a stage fails, CO retains the fault and the application explicitly calls stop; cleanup must tolerate partial initialization.

## Return cycles are not retries

A repeated line, section, or finding can be counted by an analysis layer as recurrence. It must not cause CO to rerun a failed callback automatically. Retry policy requires a separate application decision with an attempt limit, deadline, idempotency rule, and evidence record.

## Ownership boundary

- CO stores only its callback context and lifecycle state.
- The application owns input buffers, parser state, stage ordering, timeouts, and report retention.
- Kloz may be used by the application for bounded storage through caller context; CO core does not depend on it.
- SaintSI may observe successful stage heartbeats; a heartbeat is not proof of correct semantic output.
- Klipot may display the documented state machine, but its browser simulation is not this C runtime.

The canonical metadata-only exchange shape is [SAMBU Text Signal Contract v1](https://github.com/bboroski/SAMBU/blob/main/docs/MULTILINGUAL_SIGNAL_PIPELINE.md).