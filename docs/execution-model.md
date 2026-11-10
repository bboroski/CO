# CO execution model

## Design objective

CO is a small control-plane state machine. Its behavior must be reproducible from the input callbacks and explicit caller actions.

## Lifecycle

1. Initialize a runtime object with immutable callback bindings.
2. Call start from STOPPED.
3. CO marks cleanup as required before invoking init. This allows shutdown to roll back partial initialization if init fails.
4. While RUNNING, the owner calls poll. Each poll executes exactly one step callback.
5. A nonzero callback result moves the runtime to FAULTED and is returned unchanged.
6. Stop invokes shutdown at most once and returns the runtime to STOPPED.

The runtime does not retry failed callbacks automatically. Retry and recovery are policy decisions for a supervisor.

## Determinism and resource use

- No heap allocation.
- One callback per poll.
- Constant-size runtime metadata.
- No hidden worker threads.
- Cycle counter saturates at UINT32_MAX rather than wrapping silently.

The execution time of a poll is bounded only if the component's step callback is itself bounded. CO cannot make an unbounded callback deterministic.

## Concurrency contract

The API is not reentrant and is not thread-safe. The caller must serialize init/start/poll/stop and must not call the runtime recursively from one of its callbacks.

## Integration with Kloz and SaintSI

- Kloz supplies platform and memory primitives; CO stores no architecture-specific state.
- SaintSI may observe CO state and heartbeat through an adapter. CO does not directly depend on SaintSI.
- Adapters must translate result codes explicitly and must not reinterpret arbitrary callback errors as success.
