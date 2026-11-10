# CO — Control Orchestrator

**CO is a deterministic, allocation-free lifecycle runtime for embedded components.**

Its responsibility is to bring components online in a defined order, execute bounded work steps, preserve failure state, and perform cleanup after partial or complete initialization.

CO is the control layer of the NUN system. It is not an RTOS, does not create threads, and does not silently acquire hardware resources.

## Initial implementation

- Explicit lifecycle state machine.
- Caller-owned runtime object; no heap allocation.
- Init, step, and shutdown callbacks.
- Callback error propagation and fault retention.
- Saturating execution-cycle counter.
- Host unit tests for successful startup, runtime failure, and cleanup.

## State machine

```text
STOPPED --start--> STARTING --init OK--> RUNNING
                       |                    |
                    init error           step error
                       |                    |
                       +------> FAULTED <--+
                                  |
                                 stop
                                  |
                               STOPPED
```

The shutdown callback is invoked after initialization has been attempted, including partial initialization failure. It must therefore tolerate partial setup.

## Build and test

```sh
make test
make clean
```

Requires a C11 compiler and Make.

## Boundary

- CO does not own an allocator; runtime state is provided by the caller.
- CO does not implement preemption or an interrupt scheduler.
- CO does not write MMIO registers.
- CO is not internally thread-safe; the integrator serializes calls.
- Scheduling policy, priorities, deadlines, and watchdog policy remain explicit future modules.

See [docs/execution-model.md](docs/execution-model.md).
