# CO — Reaper cycle lifecycle adapter

## Mapping

CO's deterministic runtime can orchestrate one bounded simulation run through its existing init, step, and shutdown hooks:

| CO callback | Reaper cycle responsibility |
|---|---|
| init | Validate seed, iteration budget, and model version |
| step | Advance one bounded unit or a caller-defined batch |
| shutdown | Release caller-owned adapter resources and finalize diagnostics |

Do not create 6666 threads or queue 6666 unbounded jobs. The work budget is a counter inside a deterministic simulation.

## Failure semantics

A failed callback transitions CO to FAULTED. The adapter must leave partial output marked uncommitted and let CO's existing shutdown path clean up partially initialized state. A cancellation is not a successful synthesis result.

## Boundary

ReaperCripple owns the C11 reference model and its phase contract. CO remains a generic component runtime; it must not import Reaper-specific device, BIOS, or kernel responsibilities.
