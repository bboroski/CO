# Runtime diagnostics

The `co_runtime_diagnostics()` API provides a read-only snapshot of the deterministic component runtime: state key, last callback result, cycle count, cleanup obligation and currently valid operator actions. It does not call callbacks or change lifecycle state.

The snapshot distinguishes an ordinary STOPPED state from FAULTED state with cleanup still required. UI clients should disable polling unless `can_poll` is set and should surface the last result before suggesting recovery.
