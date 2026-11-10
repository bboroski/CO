# AI-Generated Plan Contract

**Scope:** CO deterministic component lifecycle runtime.  
**Status:** design boundary; no model runtime or dynamic-code loader is added.

## Principle

A model may propose a declarative plan, but CO executes only callbacks explicitly bound by the trusted host application. Model output must never create or supply native function pointers, executable code, shell commands, dynamic libraries or arbitrary callback addresses.

## Safe plan representation

A future plan format should contain only:
- stable component and step identifiers;
- an allowlisted operation name;
- declared prerequisites and required capabilities;
- bounded timeout/work hints;
- explicit cleanup identifiers;
- a schema version and provenance record.

The host resolves every identifier against a compiled allowlist. Unknown operations, duplicate step IDs, missing cleanup for resource-acquiring stages, cyclic dependencies and excessive plan length are rejected before co_runtime_start.

## Lifecycle invariants

- init and step remain trusted callbacks installed through co_runtime_init.
- Polling is cooperative and bounded; a callback cannot recursively advance the runtime.
- A failed initialization may have partially acquired resources, so the existing cleanup obligation must be honored.
- A failed step transitions to CO_STATE_FAULTED; model-generated text cannot force a return to RUNNING.
- Shutdown follows the runtime's explicit state rules and invokes cleanup at most once.
- Runtime state and result codes are authoritative; generated explanations are non-authoritative annotations.

## Test requirements

For any future plan importer, test invalid state transitions, re-entrant poll attempts, duplicate identifiers, unknown operations, dependency cycles, over-limit step counts, failed initialization with cleanup, failed step followed by shutdown and repeated shutdown. Include hostile instructions inside descriptive text to verify they are treated as data.

## No hidden autonomy

CO must not ask Gemini or another external service to decide whether a component is safe to start, retry or stop. Recovery policy remains a versioned, testable application decision.
