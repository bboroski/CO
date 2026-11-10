# Duck UI system — CO

**Scope:** design contract for optional host-side lifecycle monitors. CO itself is a small allocation-free C11 library, not a GUI application or RTOS.

## Presentation boundary

CO owns deterministic component lifecycle, bounded polling, state retention and explicit cleanup. The core does not create threads, schedule preemptively, acquire hardware resources or own an allocator. Keep all presentation concerns outside this library.

A future host panel may show the lifecycle state machine, last successful poll, execution-cycle count, callback result and retained fault. It must reflect the public state exactly; it must not silently retry, hide a fault, or imply that a running state proves application-level health.

## Duck visual tokens

The canonical machine-readable contract is [`design/duck-ui.tokens.json`](../design/duck-ui.tokens.json).

| Role | Value |
|---|---|
| Canvas | `#0D0D0D` |
| Panels | `#1A1A1A` / `#141414` |
| Primary action / focus | `#FFD600` |
| Secondary accent | `#BFA100` |
| Selected navigation | `#332B00` |
| Main / secondary text | `#E6E6E6` / `#999999` |
| Divider | `#262626` |
| Success / fault | `#4CAF50` / `#FF4444` |

Use yellow for active navigation, explicit operator actions and focus only. Lifecycle states must always include their canonical textual state names: STOPPED, STARTING, RUNNING, STEPPING, FAULTED and STOPPING.

## Host monitor requirements

- Separate lifecycle state, callback diagnostics, timing evidence and operator commands.
- Show fault retention and partial-initialization cleanup as distinct facts.
- Require explicit confirmation for stop/restart actions and show the target component.
- Support 80–160% zoom, OS DPI, keyboard navigation, visible focus, high-contrast mode and reduced motion.
- Keep logs and diagnostic reports in-app; export is optional.
- Never imply that CO provides preemption, a scheduler or independent thread safety.

## Verification boundary

The current CO repository has no desktop GUI. A diagram or future dashboard mock-up is a **design preview**, not a screenshot or a running CO instance. CO's C11 core, public ABI and tests remain independent of rendering and user-interface dependencies.
