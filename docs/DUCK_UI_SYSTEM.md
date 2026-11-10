# Amber–Obsidian UI system — CO

**Scope:** design contract for optional host-side lifecycle monitors. CO itself is a small allocation-free C11 library, not a GUI application or RTOS.

## Presentation boundary

CO owns deterministic component lifecycle, bounded polling, state retention and explicit cleanup. The core does not create threads, schedule preemptively, acquire hardware resources or own an allocator. Keep all presentation concerns outside this library.

A future host panel may show the lifecycle state machine, last successful poll, execution-cycle count, callback result and retained fault. It must reflect the public state exactly; it must not silently retry, hide a fault, or imply that a running state proves application-level health.

## Duck visual tokens

The canonical machine-readable contract is [`design/duck-ui.tokens.json`](../design/duck-ui.tokens.json).

| Role | Value |
|---|---|
| Canvas | `#0B0B0D` |
| Panels | `#1C1C1E` / `#141416` |
| Primary action / focus | `#FF9F0A` |
| Secondary accent | `#C46B12` |
| Selected navigation | `#3A2408` |
| Main / secondary text | `#F5F3EE` / `#A6A3AB` |
| Divider | `#34343A` |
| Success / fault | `#64C787` / `#F16D65` |

Use amber for active navigation, explicit operator actions and focus only. Lifecycle states must always include their canonical textual state names: STOPPED, STARTING, RUNNING, STEPPING, FAULTED and STOPPING.

## Host monitor requirements

- Separate lifecycle state, callback diagnostics, timing evidence and operator commands.
- Show fault retention and partial-initialization cleanup as distinct facts.
- Require explicit confirmation for stop/restart actions and show the target component.
- Support 80–160% zoom, OS DPI, keyboard navigation, visible focus, high-contrast mode and reduced motion.
- Keep logs and diagnostic reports in-app; export is optional.
- Never imply that CO provides preemption, a scheduler or independent thread safety.

## Verification boundary

The current CO repository has no desktop GUI. A diagram or future dashboard mock-up is a **design preview**, not a screenshot or a running CO instance. CO's C11 core, public ABI and tests remain independent of rendering and user-interface dependencies.


## Amber–Obsidian v2 alignment

This legacy design contract is aligned with the repository-specific palette and visual system v2. See [the current interface specification](INTERFACE_DESIGN.md) and the machine-readable [design tokens](../design/duck-ui.tokens.json). The project accent is #FF9F0A; secondary data signal is #B49AF4. The embedded target/library core must remain presentation-free where the product boundary requires it.
