# Closed-Domain Boundary Profile — CO

**Role:** deterministic, caller-owned C11 component lifecycle runtime.

## Transfer into lifecycle semantics

A CO runtime instance is a bounded execution domain: it has caller-owned storage, an explicit lifecycle, a finite callback surface, and a declared poll budget.

| CDM-1 concept | CO runtime feature |
|---|---|
| Bounded region | Runtime object and caller-owned component context |
| Boundary | Declared init/step/shutdown callbacks and their ownership rules |
| Fixed state | Lifecycle state snapshot before and after each callback |
| Boundary stress | Callback failure, reentrancy attempt, exhausted step/time budget |
| Conservation ledger | Saturating poll count, callback result, and lifecycle transition record |
| Isolation | No implicit thread, heap, timer, MMIO, or cross-component global state |

## Required invariants

1. Exactly one bounded `step` callback is executed per poll.
2. The runtime rejects recursive poll/stop calls while a callback is active.
3. A failed init or step remains a failure; it is never rewritten as a successful state.
4. Partial initialization still receives the documented cleanup attempt.
5. Each component owns its context; the caller serializes access across independent execution contexts.
6. Optional future budgets must be explicit input fields with deterministic limit behavior; they must not create hidden clocks or workers.

## Acceptance tests to add

- Attempt callback re-entry and verify deterministic rejection.
- Verify every lifecycle edge, including partial-init failure and cleanup.
- Verify the poll counter saturates without wrapping.
- Verify that a failed callback cannot leave the instance marked `RUNNING`.
- Verify no callback is invoked after terminal stop.

## Scope

This is a refinement of lifecycle observability and bounds. It does not expand CO into an RTOS, scheduler, autonomous recovery service, or general physical simulator.
