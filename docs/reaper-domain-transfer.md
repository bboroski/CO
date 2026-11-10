# Reaper Domain Transfer Profile — CO

**Status:** deterministic lifecycle design  
**Role:** bounded phase execution, explicit transitions and rollback-aware shutdown

## Objective

The source list describes repeated harvest cycles, autonomous protocols, memory/process stages and collective systems. CO can use those motifs to exercise deterministic multi-phase workflows, while keeping its actual scope narrow: a state machine driven by caller callbacks.

## Phase model

A long-running workflow should be represented as explicit phases, not a monolithic callback. Each phase has a stable ID, input version, bounded step callback, completion result and cleanup responsibility. The owner still calls `poll`; one poll must execute no more than the documented unit of work.

Example declarative lifecycle:

`DISCOVERED → VALIDATED → PREPARED → RUNNING → REVIEWED → COMPLETE`

An error transitions to `FAULTED`; explicit `stop` performs cleanup once. A supervisor may choose whether to retry or recover, but CO must not invent that policy. Partial initialization must remain rollback-safe.

## Event semantics

Where an adapter records lifecycle events, include runtime ID, phase ID, sequence, caller timebase, callback result and state-before/state-after. Events are diagnostic evidence, not proof that an external action completed unless the callback returned a documented success result.

## Transfer from the Reaper taxonomy

- **Harvest cycle:** a versioned workflow epoch with an explicit start and terminal state.
- **Processing stage:** one bounded callback/phase.
- **Autonomous protocol:** caller-owned orchestration; no hidden worker thread or retry.
- **Core reconstruction:** a new runtime instance with a new identity, not mutation of a completed instance.
- **Collective consciousness:** multiple runtimes coordinated by an external supervisor; CO itself remains single-instance and non-distributed.

## Invariants

- No implicit heap allocation, background thread, interrupt scheduling or network activity.
- One callback per poll and explicit handling of reentrancy.
- Callback error codes are propagated unchanged.
- Stop/rollback is called at most once per initialized instance.
- Cycle counters and event sequences have defined saturation/rollover behavior.
- A phase cannot be skipped merely because its name resembles a lore concept.

## Suggested validation

Test illegal phase jumps, repeated completion, failure in every phase, partial-init cleanup, callback reentrancy, event sequence rollover, stop during a callback and deterministic replay from the same scripted callback outcomes.

These are lifecycle patterns inspired by the terminology; CO remains a generic component runtime and has no Mass Effect-specific runtime dependency.
