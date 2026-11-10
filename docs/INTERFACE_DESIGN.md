# CO — Amber–Obsidian interface specification

## Product identity

**CO** — Deterministic lifecycle and component orchestration runtime. This specification describes a future operator-facing presentation for the library; it does not claim that a desktop application or live telemetry surface is implemented.

## Visual direction

- Obsidian canvas: `#0B0B0D`.
- Graphite panels: `#141416`, `#1C1C1E`, `#2C2C30`; border: `#34343A`.
- Domain amber: `#FF9F0A`; pressed state: `#C46B12`.
- Secondary signal: `#B49AF4`.
- Text: `#F5F3EE`; secondary: `#C8C3BA`; muted: `#A6A3AB`.
- State language: passed `#64C787`; caution `#FFBF47`; fault `#F16D65`; unknown `#A78BFA`.

## Operator surfaces

1. **LIFECYCLE** — RUNNING.
2. **CALLBACK SEQUENCE** — 000042.
3. **FAULT REGISTER** — 0 RETAINED.

CO is a portable lifecycle library, not a desktop product. Present the runtime state as a documented diagnostic panel or future test-console concept; the preview does not represent a shipped GUI.

## Interaction and accessibility contract

Use explicit text labels for all states, show numeric values in monospaced tabular typography, expose evidence coverage separately from result quality, maintain 36×36 px targets where an interactive shell exists, provide keyboard focus, and respect reduced-motion preferences. No status transition is implied by a decorative animation.

## Reference artwork

- [Project mark](../assets/amber-obsidian-mark.svg)
- [Interface concept preview](../assets/amber-obsidian-preview.svg)

The preview is a static design reference, not a live view of the library.

## Tokens

```css
:root {
  color-scheme: dark;
  --ao-canvas: #0B0B0D;
  --ao-surface-1: #141416;
  --ao-surface-2: #1C1C1E;
  --ao-surface-3: #2C2C30;
  --ao-border: #34343A;
  --ao-text: #F5F3EE;
  --ao-muted: #A6A3AB;
  --ao-accent: #FF9F0A;
  --ao-accent-pressed: #C46B12;
  --ao-secondary: #B49AF4;
  --ao-success: #64C787;
  --ao-warning: #FFBF47;
  --ao-danger: #F16D65;
}
```
