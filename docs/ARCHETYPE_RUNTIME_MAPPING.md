# CO: bounded control and the five engineering patterns

CO remains a deterministic lifecycle state machine. The archetypes extend the integration discipline; they do not turn CO into an RTOS or a hidden task scheduler.

## Alucard — resource admission, not limit removal

A caller may combine CO with Kloz resource budgets. Before scheduling optional work, the adapter checks memory, queue and work reservations. If admission fails, the adapter defers or rejects that work and preserves the CO runtime state. An emergency policy may shed optional tasks, but it must not raise the configured ceilings.

CO cannot preempt a callback that exceeds its execution budget. Each `step` callback must therefore have a documented worst-case execution bound or split its operation into smaller cooperative steps.

## Shanks — autonomy without an accidental distributed lock

Each CO runtime is caller-owned and independently controlled. Multiple components can progress without a global mutex when their owners provide the required synchronization. CO itself is not a gossip protocol, consensus system or distributed lease manager.

For multi-node deployments, a separate coordinator may distribute non-critical state. Any exclusive side effect must use an authoritative epoch/fencing mechanism. A stale node must not resume firmware writes or actuator control after losing ownership.

## Nun — explicit transitions and replayable evidence

The runtime state, last callback result and cycle counter are deterministic observations. An integration adapter may record `start`, `poll`, `fault` and `stop` as versioned events. CO does not own a persistent event log; recording, rotation and replay are integration responsibilities.

A replay harness should replace hardware callbacks with deterministic fakes. It must never replay a destructive hardware action against a live board.

## Ging Freecss — explicit contracts

The callback table is a small interface contract: context, init, step and shutdown. Keep preconditions, postconditions, resource ownership and cleanup requirements next to the adapter. Configuration should select reviewed callback sets rather than evaluate arbitrary untrusted code.

Self-describing interfaces are useful; intentionally cryptic documentation is not.

## Jinn — cooperative work and isolation

On bare metal, represent deferred work as bounded state machines that perform a small amount of work during each CO poll. A fixed-size mailbox may be owned by the application or an adapter, but it must define capacity, overflow behavior and cancellation.

On a host OS, heavyweight or untrusted tasks belong in a separately supervised process or VM with explicit permissions and quotas. A CO callback is not a process sandbox, daemon or actor runtime.

## Integration boundary

```text
Kloz platform/time/resource primitives
              |
              v
        CO lifecycle
              |
              +---- adapter reports completed progress to SaintSI
              |
              +---- ReaperCripple owns board-specific recovery policy
```

CO must not call SaintSI directly or access Kloz hardware-specific internals. Translate result codes at the integration boundary and preserve callback failures unchanged unless a documented adapter mapping says otherwise.

## Acceptance checks

- A callback executes at most once per `co_runtime_poll()`.
- Recursive poll/stop is rejected while a callback is active.
- Partial initialization always has a defined cleanup path.
- A failed callback is not automatically retried.
- Each callback's time and resource assumptions are documented and tested.
- No test implies thread safety, preemption or hardware qualification without target-specific evidence.
