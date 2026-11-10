# Federated reliability model

CO owns the deterministic lifecycle of a component instance. Components own their callbacks and state; the runtime owns sequencing and cleanup guarantees.

## Lifecycle rules

- Initialization, polling and shutdown are explicit hooks.
- Only a running component may be polled; recursive polling is rejected by the state machine.
- A failed initialization or step enters `FAULTED` and preserves the cleanup obligation.
- Shutdown is idempotent for stopped instances and invokes cleanup at most once for each acquired lifecycle.

## Coordination boundary

- The optional SaintSI bridge reports heartbeat freshness only after a successful running-state check.
- A heartbeat is a liveness signal, not proof that a component's output is correct.
- CO does not make distributed policy decisions, deploy components or invent recovery actions.
- Cross-component policy remains outside the runtime and is passed through explicit hooks.

## Verification gate

Run `make test`. Host tests cover start/step/fault/cleanup ordering; target scheduling and concurrency assumptions need separate platform-level evidence.
