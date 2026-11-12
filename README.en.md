# CO
**Deterministic Component Lifecycle Runtime**

[Українська](README.md) · [English](README.en.md) · [Русский](README.ru.md)

A compact C11 runtime for predictable component startup, stepping and shutdown without requiring a full RTOS.

## Features
- Explicit STOPPED, STARTING, RUNNING, STEPPING, FAULTED and STOPPING states.
- Runtime storage is supplied by the caller; no heap allocation.
- init, step and shutdown callbacks with error propagation.
- Recursion guards and host tests for fault and partial-initialization paths.

## Run and test
```bash
make test
python one.py check
```

## Scope
CO is a C11 runtime without a graphical interface; no genuine application screenshots are available.

CO does not implement preemption, an interrupt scheduler or MMIO. The caller serializes access across independent contexts; scheduling and watchdog policy remain external.

## Project documentation

*Static ecosystem diagram, not a CO application screenshot.*

## Related
[Documentation](docs/) · [API headers](include/)

[Kloz](https://github.com/bboroski/Kloz) · [SaintSI](https://github.com/bboroski/SaintSI)

## License
No root license file is declared; review the repository terms before reuse.

---
**心心相印。**
*Two hearts understand each other without words.*
— Chinese idiom
