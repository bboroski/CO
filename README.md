# CO — Control Orchestrator

**CO is a deterministic, allocation-free lifecycle runtime for embedded components.**

Its responsibility is to bring components online in a defined order, execute bounded work steps, preserve failure state, and perform cleanup after partial or complete initialization.

CO is the deterministic lifecycle-control layer in the unified embedded runtime stack. It is not an RTOS, does not create threads, and does not silently acquire hardware resources.

## Initial implementation

- Explicit lifecycle state machine, including a guarded STEPPING state.
- Caller-owned runtime object; no heap allocation.
- Init, step, and shutdown callbacks.
- Callback error propagation and fault retention.
- Saturating execution-cycle counter.
- Reentrant poll/stop attempts are rejected while a callback is executing.
- Host unit tests for startup, execution failure, partial-init cleanup, and recursion guards.

## State machine

```text
STOPPED --start--> STARTING --init OK--> RUNNING
                       |                    |
                    init error             poll
                       |                    v
                       +------> FAULTED  STEPPING
                                  ^        |   |
                                  |        |   +-- step OK --> RUNNING
                                  +--------+
                                   step error

FAULTED --stop--> STOPPING --> STOPPED
RUNNING --stop--> STOPPING --> STOPPED
```

The shutdown callback is invoked after initialization has been attempted, including partial initialization failure. It must therefore tolerate partial setup.

## Build and test

```sh
make test
make clean
```

Requires a C11 compiler and Make. GitHub Actions runs the host tests with GCC and Clang.

## Boundary

- CO does not own an allocator; runtime state is provided by the caller.
- CO does not implement preemption or an interrupt scheduler.
- CO does not write MMIO registers.
- The caller serializes access from independent execution contexts.
- Scheduling policy, priorities, deadlines, and watchdog policy remain explicit future modules.

See [docs/execution-model.md](docs/execution-model.md) and [the cross-repository integration contract](docs/PLATFORM_INTEGRATION.md).
