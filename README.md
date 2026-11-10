# CO — Control Orchestrator

**CO is a deterministic, allocation-free lifecycle runtime for embedded components.**

Its responsibility is to bring components online in a defined order, execute bounded work steps, preserve failure state, and perform cleanup after partial or complete initialization.

CO is the control layer of the SAMBU Ecosystem. It is not an RTOS, does not create threads, and does not silently acquire hardware resources.

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

See [docs/execution-model.md](docs/execution-model.md).


## SAMBU Ecosystem integration

<p align="center"><img src="https://raw.githubusercontent.com/bboroski/SAMBU/main/assets/sambu-ecosystem-overview.svg" width="100%" alt="CO highlighted within the SAMBU Ecosystem project ecosystem"></p>

CO owns deterministic component lifecycle: initialization, one bounded step per poll, fault retention and cleanup. Its portable state machine remains independent of any OS, hardware register map or health policy.

## SAMBU connections

- **Kloz:** an application may place a validated Kloz platform-ops pointer in callback context. CO itself does not call MMIO or require Kloz.
- **SaintSI:** call the optional bridge after a successful start and after each completed poll. A faulted runtime deliberately stops refreshing its heartbeat so the observer can report staleness.
- **ReaperCripple:** a Reaper bootstrap stage may own a CO runtime as a component service; cleanup must remain explicit and reverse-ordered.
- **Klipot:** the portal lists the contract and offers a state-machine simulation; that simulation is not this C runtime.

## Integration boundary

The optional header include/co/saintsi_bridge.h requires both include roots on the consumer's include path. It does not change the core library or build flags. The host application supplies the timebase in SaintSI ticks and decides what a degraded result means.

See the [SAMBU integration protocol](https://github.com/bboroski/Klipot/blob/main/docs/INTEGRATION_PROTOCOL.md) and [SaintSI](https://github.com/bboroski/SaintSI).


[Shared integration protocol](https://github.com/bboroski/Klipot/blob/main/docs/INTEGRATION_PROTOCOL.md) · [Klipot control portal](https://github.com/bboroski/Klipot)


## Multilingual pipeline lifecycle

CO can run each analysis stage as one bounded callback and retain failures without hidden retries. See [Signal Pipeline Lifecycle](docs/SIGNAL_PIPELINE_LIFECYCLE.md) and the [SAMBU metadata contract](https://github.com/bboroski/SAMBU/blob/main/docs/MULTILINGUAL_SIGNAL_PIPELINE.md).

## SAMBU Ecosystem module

CO remains the allocation-free C11 lifecycle runtime. Kloz services are optional application-supplied adapters, not a required CO core dependency.

- **Module manifest:** [`sambu.module.json`](sambu.module.json)
- **Canonical architecture:** [SAMBU Ecosystem Architecture](https://github.com/bboroski/SAMBU/blob/main/docs/ECOSYSTEM_ARCHITECTURE.md)
- **Shared integration protocol:** [Klipot protocol](https://github.com/bboroski/Klipot/blob/main/docs/INTEGRATION_PROTOCOL.md)


[SAMBU Ecosystem portal](https://bboroski.github.io/Klipot/) · [Klipot integration protocol](https://github.com/bboroski/Klipot/blob/main/docs/INTEGRATION_PROTOCOL.md)


## One-knob workflow / Один запуск / Запуск однією командою

- **Windows:** double-click `one.cmd` or run `./one.cmd`.
- **Any OS:** run `python one.py` to build and execute this module's host verification in one step.
- **Verification only:** run `python one.py check`. Host tests do not replace target timing, board, DMA, IRQ or hardware qualification.


---

## Duck UI system

This repository follows the shared black/graphite and signal-yellow visual contract for its applicable user-facing tools. See [Duck UI System](docs/DUCK_UI_SYSTEM.md), the canonical [design tokens](design/duck-ui.tokens.json), and the scalable [duck mark](assets/duck-ui/duck-mark.svg). UI previews are explicitly distinguished from real runtime screenshots; embedded cores remain presentation-agnostic.
