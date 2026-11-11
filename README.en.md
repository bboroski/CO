<p align="center"><img src="assets/duck-ui/duck-mark.svg" alt="CO mark" width="92"></p>
<h1 align="center">CO</h1>
<p align="center"><strong>Deterministic Component Lifecycle Runtime</strong></p>
<p align="center"><img src="https://img.shields.io/badge/STATUS-HOST%20TESTED%20CORE-FFD600?style=for-the-badge&labelColor=111111"><img src="https://img.shields.io/badge/CORE-C11-FFD600?style=for-the-badge&labelColor=111111"><img src="https://img.shields.io/badge/LICENSE-NOT%20DECLARED-FFD600?style=for-the-badge&labelColor=111111"></p>
<p align="center"><a href="README.md">🇺🇦 Українська</a> · <a href="README.en.md">🇬🇧 English</a> · <a href="README.ru.md">🇷🇺 Русский</a></p>

---

**CO is a compact C11 runtime for predictable component startup, step execution, and shutdown.** It provides an explicit lifecycle without requiring a full RTOS and leaves memory ownership and execution context with the caller.

## Implemented features

- Explicit state machine, including the guarded <code>STEPPING</code> state.
- Runtime object stored in caller-provided memory; no heap is used.
- <code>init</code>, <code>step</code>, and <code>shutdown</code> callbacks.
- Callback error propagation and last-result retention.
- Saturating execution-cycle counter.
- Recursive <code>poll</code>/<code>stop</code> rejection during callbacks.
- Host tests for startup, errors, partial initialization, and reentrancy protection.

## State model

~~~text
STOPPED -> STARTING -> RUNNING -> STEPPING -> RUNNING
              |          |          |
              +--------> FAULTED <---+
FAULTED -> STOPPING -> STOPPED
RUNNING -> STOPPING -> STOPPED
~~~

The shutdown callback runs after an initialization attempt, including partial failure, and must therefore handle incomplete setup safely.

## Build and verify

Requires a C11 compiler and Make.

~~~sh
make test
make clean
python one.py check
~~~

GitHub Actions runs host tests with GCC and Clang.

## Governance and release criteria

| Control | Rule |
|---|---|
| Memory | Runtime uses caller-provided memory |
| Lifecycle | States and errors are explicit |
| Callback safety | Recursive poll/stop calls are rejected |
| Host CI | GCC and Clang checks must pass |
| Integration | The caller serializes access across independent contexts |

## Responsibility boundaries

CO does not own an allocator or create a heap; it does not implement preemption, an interrupt scheduler, or MMIO access. The caller serializes access across independent contexts. Scheduling policy, priorities, deadlines, and watchdogs belong to separate modules. The canonical API uses the <code>co_</code> prefix; the legacy <code>co/runtime.h</code> header provides source-level aliases.

Documentation: [execution model](docs/execution-model.md).

## Ecosystem and license

Related projects: [SAMBU](https://github.com/bboroski/SAMBU), [ToolNG](https://github.com/bboroski/ToolNG), [ReaperCripple](https://github.com/bboroski/ReaperCripple), [Kloz](https://github.com/bboroski/Kloz), [SaintSI](https://github.com/bboroski/SaintSI), [Klipot](https://github.com/bboroski/Klipot), [NUN](https://github.com/bboroski/NUN), and [NUNLauncher](https://github.com/bboroski/NUNLauncher).

**No license is declared:** the repository has no <code>LICENSE</code> file. Define the terms and add the full license text before redistribution.

---

**Built with love for predictable code and people.**

## Product system

Shared Duck design, multilingual documentation, capability governance, marketing-claim controls and release rules: [docs/PRODUCT_SYSTEM.md](docs/PRODUCT_SYSTEM.md). The 10,000-ID registry is planning capacity, not a claim of 10,000 shipped functions.
