<p align="center"><img src="assets/duck-ui/duck-mark.svg" alt="Duck mark" width="104" /></p>
<h1 align="center">CO</h1>
<p align="center"><strong>Deterministic Component Lifecycle Runtime</strong></p>
<p align="center"><img src="https://img.shields.io/badge/STATUS-HOST-TESTED%20CORE-FFD600?style=for-the-badge&labelColor=111111" /><img src="https://img.shields.io/badge/CORE-C11-FFD600?style=for-the-badge&labelColor=111111" /><img src="https://img.shields.io/badge/LICENSE-TEXT%20MISSING-FFD600?style=for-the-badge&labelColor=111111" /></p>
<p align="center"><a href="README.md">🇺🇦 Українська</a> · <a href="README.en.md">🇬🇧 English</a> · <a href="README.ru.md">🇷🇺 Русский</a></p>
<hr />

<p align="center"><img src="assets/nun-mesh.svg" alt="CO in the repository integration mesh" width="100%"></p>


**A compact C11 runtime for predictable startup, work steps, and shutdown of embedded components.**

## Product position

CO provides an explicit lifecycle for components that do not need a full RTOS. It separates initialization, work, failure, and shutdown while leaving memory ownership and execution context under caller control.

## Implemented capabilities

- Explicit state machine, including the guarded <code>STEPPING</code> state.
- Runtime object backed by caller-owned memory; no heap is used.
- <code>init</code>, <code>step</code>, and <code>shutdown</code> callbacks.
- Callback error propagation and preservation of the last result.
- Saturating execution-cycle counter.
- Rejection of recursive <code>poll</code>/<code>stop</code> calls during a callback.
- Host tests for startup, failures, partial initialization, and recursion protection.

## State model

~~~text
STOPPED -> STARTING -> RUNNING -> STEPPING -> RUNNING
              |          |          |
              +--------> FAULTED <---+
FAULTED -> STOPPING -> STOPPED
RUNNING -> STOPPING -> STOPPED
~~~

The shutdown callback is invoked after an initialization attempt, including partial failure. It must handle incomplete setup safely.

## Build and verify

Requires a C11 compiler and Make.

~~~sh
make test
make clean
~~~

GitHub Actions runs host tests with GCC and Clang. One-knob runner: <code>python one.py</code>; checks: <code>python one.py check</code>.

## Project management and release gates

| Gate | Rule |
|---|---|
| Memory | Runtime uses caller-provided storage |
| Lifecycle | States and failures are explicit |
| Callback safety | Recursive poll/stop calls are rejected |
| Host CI | GCC and Clang checks must pass |
| Integration | The caller serializes access across independent execution contexts |

## Responsibility boundaries

- CO does not own an allocator and does not create a heap.
- CO does not implement preemption or an interrupt scheduler.
- CO does not write MMIO registers.
- The caller serializes access from independent execution contexts.
- Scheduling policy, priorities, deadlines, and watchdog remain separate modules.

The canonical API uses the <code>co_</code> prefix. The old <code>co/runtime.h</code> header provides source-level aliases; binaries using old symbols must be relinked.

## Documentation

- [Execution model](docs/execution-model.md)

## Ecosystem

[SAMBU](https://github.com/bboroski/SAMBU) · [ToolNG](https://github.com/bboroski/ToolNG) · [ReaperCripple](https://github.com/bboroski/ReaperCripple) · [Kloz](https://github.com/bboroski/Kloz) · [SaintSI](https://github.com/bboroski/SaintSI) · [Klipot](https://github.com/bboroski/Klipot) · [NUN](https://github.com/bboroski/NUN) · [NUNLauncher](https://github.com/bboroski/NUNLauncher).

## License

Earlier project documentation declared MIT, but this repository has no LICENSE file. Confirm the license and add its full text before distribution.
