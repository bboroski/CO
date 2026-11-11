# Inter-substrate runtime profile — CO

**Contract:** [SAMBU runtime API v1](https://github.com/bboroski/SAMBU/blob/feat/substrate-runtime-contract-v1/docs/INTERSUBSTRATE_RUNTIME_API_V1.md)  
**Status:** repository-specific integration profile; not a blanket implementation claim.

## Ownership
Deterministic component lifecycle runtime (C11, allocation-free caller-owned state).

## Existing evidence
Explicit lifecycle states, init/step/shutdown callbacks, fault retention, partial-init cleanup, bounded poll and reentrancy guards.

## Integration slice
Treat each component instance as an owned resource with a stable ID, explicit lifetime and capability list. Bridge lifecycle transitions to event envelopes through a caller-provided callback; do not add hidden threads or an implicit event loop. Define callback ordering, sequence, timeout budget, queue-full behavior and rollback semantics. Require the application to serialize calls from independent contexts.

## Explicit non-goals
CO is not an RTOS, process container, microservice host, preemptive scheduler, interrupt controller or distributed transaction coordinator. It must not silently create locks, threads, retries or MMIO access.

## Acceptance tests
Test all legal/illegal state transitions, callback ordering, recursive poll/stop rejection, partial-init rollback, queue-full status propagation, duplicate event delivery policy and concurrent-call contract (caller serialization or explicit rejection).

## Capability maturity
- Existing features retain their current maturity and evidence.
- The central envelope, descriptor validator, JSON codec, and bounded local queue are a SAMBU host reference, not a distributed runtime service.
- This profile does not authorize hardware changes, network egress, process execution, or access to another repository.
