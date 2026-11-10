# Reaper-Domain Integration — CO

**Role:** deterministic component lifecycle runtime  
**Canonical catalogue:** [SAMBU — 50 curated engineering patterns](https://github.com/bboroski/SAMBU/blob/main/data/reaper/engineering_patterns_50.tsv)

## Engineering transfer

The Harvest Cycle is useful as a scenario for repeatable phases, not as a literal runtime schedule. CO should model lifecycle as explicit, validated transitions:

`STOPPED → STARTING → RUNNING → STEPPING → RUNNING`

Failures enter `FAULTED`; the caller owns retry and recovery policy. The Crucible concept maps to an integration gate: a composite starts only after every required component has completed its declared initialization.

## Runtime constraints

- Exactly one bounded step callback per poll.
- No implicit worker thread, allocator, timer, or hardware access.
- Preserve callback errors; do not reinterpret a failed stage as success.
- Cleanup after partial initialization remains explicit and idempotent.
- Any future staged-work helper must declare its maximum step count and execution budget.

## Acceptance

Keep CO a small, independently buildable C11 state machine. Reaper terminology may inform examples and scenario tests, but it must not enlarge the runtime into an RTOS, scheduler, or autonomous recovery controller.
