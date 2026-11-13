# Multi-Axis Layer Architecture

**Architecture:** NUN Mesh — Multi-Axis Layer Fabric (MALF)  
**Repository:** `bboroski/CO`  
**Role:** Deterministic, allocation-free C11 component lifecycle runtime  
**Maturity:** Host-tested C11 core; scheduling and target timing belong to the consuming application/platform.  
**Status:** Target boundary contract; implementation claims remain evidence-based.

## Purpose

MALF makes layering explicit across structural boundaries, vertical feature slices, trust boundaries, lifecycle stages and assurance planes. This is not a folder-renaming exercise: preserve working source layout until a tested refactor proves a benefit.

## Structural layers

| ID | Layer | Responsibility |
|---|---|---|
| L0 | **Experience** | CLI, GUI and operator surface. |
| L1 | **Interface contracts** | Public APIs, ABIs, schemas, events and versioned formats. |
| L2 | **Application orchestration** | Use cases, sequencing, lifecycle and transaction boundaries. |
| L3 | **Domain kernel** | Deterministic models, algorithms and invariants. |
| L4 | **Policy and capabilities** | Authorization, resource limits, safety and allowed operations. |
| L5 | **Ports and contracts** | Abstract platform, clock, storage, memory and device services. |
| L6 | **Adapters and platform** | Concrete OS, CPU, board and hardware implementations. |
| L7 | **State and data** | Persisted state, caller-owned memory, schemas and artifacts. |
| L8 | **Runtime and delivery** | Build, boot, packaging, deployment and execution composition. |
| L9 | **Assurance and evidence** | Tests, static analysis, resource proofs and target qualification. |

Layers describe ownership, not mandatory directories. Small libraries may collapse layers; split only where isolation, API ownership, testing or platform variation requires it.

## Dependency law

- L0 calls application use cases at L2 using L1; presentation owns no core rules.
- L2 coordinates L3/L4 through L5.
- L6 implements L5; the domain must not import a board, OS, vendor SDK or GUI.
- L7 state is accessed through explicit memory/storage contracts.
- L8 composes inner layers; the kernel/domain never depends on deployment.
- L9 verifies both behavior and boundaries.

**Allowed:** surface → application → domain/policy → port → adapter.  
**Forbidden:** domain → platform adapter; hidden globals; undeclared cross-repository source coupling.

## Orthogonal architecture axes

1. **Structural:** L0–L9 responsibilities.
2. **Vertical slices:** a capability crosses only the layers it needs, with explicit input, decision, effect, state and tests.
3. **Trust:** untrusted input → validation → capability/policy gate → authorized effect → observable result.
4. **Lifecycle:** design → configure → build → verify → package → deploy/boot → operate → recover → retire.
5. **Assurance/observability:** bounded evidence with provenance; a test or heartbeat proves only what it actually measures.

## Repository-specific allocation

### L0 — Consumer integration surface
C API and callback registration from the host application; no GUI or scheduler embedded.

### L1 — Lifecycle contracts
Versioned component descriptors, callback signatures, state enum and error/status ABI.

### L2 — Lifecycle orchestration
Deterministic start, poll/step, stop and partial-initialization cleanup with bounded transitions.

### L3 — Lifecycle state machine
STOPPED, STARTING, RUNNING, STEPPING, FAULTED and STOPPING invariants, ordering and fault retention.

### L4 — Execution and resource policy
Caller-owned runtime memory, explicit reentrancy behavior, serialized access contract and bounded work per poll.

### L5 — Host/platform service ports
Optional caller-supplied clock, diagnostics and platform context; core does not require Kloz.

### L6 — Application adapters
Consumer-specific component wrappers, scheduler integration and optional Kloz bridges outside the CO core.

### L7 — Runtime state
Runtime state and component context remain in caller-provided memory with explicit lifetime.

### L8 — Build and composition
Portable C11 Make/CMake build, static library integration and consumer-selected scheduling.

### L9 — Lifecycle assurance
Host tests for normal flow, partial init, callback failures, fault retention, recursive calls and deterministic cleanup.

## Vertical slices

1. **Component startup:** Consumer registers callbacks → validate descriptor → initialize in order → expose RUNNING only after success.
2. **Bounded poll:** Application schedules poll → reentrancy guard → one deterministic step → propagate status → optional external heartbeat.
3. **Fault and shutdown:** Callback failure → retain FAULTED state → reject invalid transitions → controlled shutdown/cleanup with test evidence.

## Cross-cutting planes

- **Safety/security:** least privilege, explicit capabilities, default-deny for unsupported effects, validated inputs.
- **Reliability:** bounded work and memory, explicit error/fault states, deterministic cleanup.
- **Compatibility:** version ABI, API, platform ops and persisted formats.
- **Observability:** traceable status and provenance; diagnostics do not silently trigger control actions.
- **Performance:** measure target execution and resource use; host measurements are not board qualification.
- **Accessibility:** apply to user-facing tools and docs.

## NUN Mesh federation

This repository remains independently buildable. Cross-repository integration is via versioned, optional contracts declaring provider, consumer, version, failure behavior and evidence—not implicit linking or forced runtime dependencies.

## Adoption sequence

1. Inventory current symbols and files against L0–L9.
2. Identify call cycles, hidden global state and direct platform assumptions.
3. Stabilize public L1 and port L5 contracts.
4. Keep deterministic L3 behavior isolated from platform details.
5. Enforce L4 capability/resource rules before side effects.
6. Implement target adapters at L6 and explicit state handling at L7.
7. Compose via L8 and verify invariants at L9.
8. Refactor one vertical slice per change with compatibility and rollback evidence.

## Definition of done

Ownership is explicit; dependencies point inward; contracts are versioned; resource/error behavior is tested; and maturity labels match source, tests and target evidence.

## Repository guardrails

CO is not a preemptive scheduler, RTOS, interrupt scheduler, watchdog manager or MMIO layer. The application serializes independent execution contexts. Optional Kloz/SaintSI bridges stay adapters; the CO core has no hard dependency on them.
