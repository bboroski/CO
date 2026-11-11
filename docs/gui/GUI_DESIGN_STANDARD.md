# GUI / Visual System Standard

> Host-application contract. CO is an allocation-free lifecycle runtime, not a GUI toolkit.

## Visual identity

| Token | Value | Use |
|---|---|---|
| Primary yellow | `#FFCC00` | Main action and selected state |
| Highlight yellow | `#FFE600` | Focus, hover and progress |
| Black / graphite | `#000000` / `#1A1A1A` | Structure and panels |
| Error red | `#E53935` | Fault and critical state |
| Signal cyan | `#29B6F6` | Active execution and data flow |
| White | `#FFFFFF` | Text and high-contrast details |

Existing Duck UI tokens and assets remain canonical. Change shared tokens only together with all dependent styles, previews and tests.

## Host workspace layout

An optional host UI may show a header (mark, measured runtime state, progress/activity trace and local time), lifecycle/event canvas, contextual controls and pager where multiple views exist. `55 / ~~~ / 21:33` are illustrative placeholders, not real status values. Show source and freshness of measurements.

## Runtime boundary and behavior

- CO remains headless; UI is a host client and cannot create a scheduler, RTOS, hidden heap or interrupt controller.
- Display the real state machine, callback result, bounded poll result and retained fault state.
- `init`, `step` and `shutdown` ordering must be visible and traceable where the host exposes it.
- Reentrancy guards and caller-serialized access remain mandatory; UI clicks must not bypass runtime state checks.
- Pending work needs explicit running/succeeded/failed/cancelled/timeout states. Never fake progress.
- Drawings/annotations are explanatory metadata, not executable component configuration unless a validated schema says so.

## Accessibility and evidence

Provide semantic labels, visible keyboard focus, icon/text status cues, responsive scaling and reduced-motion support. Target WCAG AA contrast (4.5:1 normal text; 3:1 large text) and 44×44 CSS-pixel touch targets where applicable. Concept wireframes are labelled; screenshots come from runnable host software.

## Release gate

Document host API integration, empty/loading/error states, callback safety, timeout behavior, focus and responsive behavior. Host UI evidence does not replace C11 host tests or target-specific timing validation.

## Українська

CO залишається headless runtime життєвого циклу компонентів; графічний інтерфейс належить зовнішній host-програмі. Він може показувати фактичні стани, результати callback і помилки, але не обходить reentrancy guards чи вимогу серіалізації. Жовтий `#FFCC00` — дія, `#FFE600` — фокус, червоний `#E53935` — fault, блакитний `#29B6F6` — активність. `55 / ~~~ / 21:33` — лише приклад макета.

## Русский

CO остаётся headless runtime жизненного цикла компонентов; графический интерфейс принадлежит внешней host-программе. Он может показывать фактические состояния, результаты callback и ошибки, но не обходит reentrancy guards или требование сериализации. Жёлтый `#FFCC00` — действие, `#FFE600` — фокус, красный `#E53935` — fault, голубой `#29B6F6` — активность. `55 / ~~~ / 21:33` — только пример макета.
