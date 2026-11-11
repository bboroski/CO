# Engineering Pattern Integration — CO

**Role:** deterministic component lifecycle runtime  
**Reference catalogue:** [SAMBU — 50 engineering patterns](https://github.com/bboroski/SAMBU/blob/main/data/reaper/engineering_patterns_50.tsv)

## Lifecycle mapping

CO models runtime progression as explicit, validated transitions:

`STOPPED → STARTING → RUNNING → STEPPING → RUNNING`

Failures enter `FAULTED`; the caller owns retry and recovery policy. Composite activation is permitted only after every required component completes its declared initialization and reports a valid result.

## Runtime constraints

- Exactly one bounded step callback per poll.
- No implicit worker thread, allocator, timer or hardware access.
- Preserve callback errors; never reinterpret a failed stage as success.
- Cleanup after partial initialization remains explicit and idempotent.
- Every staged-work helper must declare its maximum step count and execution budget.

## Acceptance

Keep CO a small, independently buildable C11 state machine. Reference scenarios must not enlarge the runtime into an RTOS, scheduler or autonomous recovery controller.
