# Domain Capabilities

CO turns collective-intelligence, neural-network and lifecycle concepts into
a bounded, deterministic quorum decision API.

## Implemented capability

- **Geth consensus / collective consciousness:** `co_consensus_evaluate` tallies
  one valid vote per node for a caller-supplied epoch.
- **Consensus override / stale signal handling:** votes from other epochs are
  counted as stale and excluded from the current decision.
- **Distributed intelligence:** fixed upper bound of 64 votes; no heap allocation.
- **Conflict detection:** a tied leading proposal without quorum is reported as
  `CO_CONSENSUS_CONFLICT`, not silently resolved.
- **Algorithmic decision gate:** only a strict majority quorum may be configured.

## Verification

`make test` builds and runs the consensus regression tests alongside the lifecycle tests.

## Boundaries

This is a local tally helper, not a distributed consensus protocol. It does not
authenticate node identities, encrypt messages, prevent network replay by itself,
persist decisions, or provide fault-tolerant replication. The application owns
transport, identity, epoch management, and serialization.
