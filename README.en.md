# DLO — Deterministic Lifecycle Orchestrator

**A deterministic C11 lifecycle runtime for embedded components.**

DLO brings components online in a defined order, executes bounded work steps, preserves failure state, and performs cleanup after partial or complete initialization. It does not create threads, implement an RTOS, or silently acquire hardware resources.

[Українська](README.md) · [English](README.en.md) · [Русский](README.ru.md)

## Implemented capabilities

- Explicit lifecycle state machine, including a guarded STEPPING state.
- Caller-owned runtime object; no heap allocation.
- init, step, and shutdown callback interface.
- Callback error propagation and retained last result.
- Saturating execution-cycle counter.
- Recursive poll/stop calls are rejected while a callback is executing.
- Host tests for startup, execution failure, partial-init cleanup, and recursion guards.

## State model

~~~text
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
~~~

The shutdown callback runs after initialization has been attempted, including partial initialization failure. It must therefore tolerate incomplete setup.

## Build and test

~~~sh
make test
make clean
~~~

Requires a C11 compiler and Make. GitHub Actions runs host tests with GCC and Clang.

## Responsibility boundary

- DLO does not own an allocator; runtime storage is supplied by the caller.
- DLO does not implement preemption or an interrupt scheduler.
- DLO does not write MMIO registers.
- The caller serializes access from independent execution contexts.
- Scheduling policy, priorities, deadlines, and watchdog policy remain separate modules.

The canonical API uses the dlo_ prefix. The legacy co/runtime.h header provides source-level aliases; binaries linked against previous symbols must be relinked.

## Documentation

- [Execution Model](docs/execution-model.md)

## License

MIT — see [LICENSE](LICENSE).


## One-knob launch

- **Windows:** double-click `one.cmd` or run it from a terminal.
- **Any OS:** `python one.py` performs the default host build and tests; `python one.py check` requests verification explicitly.
- This remains an independent C11 library; host tests do not replace integration testing on the target platform.
