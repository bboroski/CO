# Anti-Teradayn Protocol — CO

**Status:** repository-level engineering standard. Implementation claims require source, tests, and target evidence.  
**Scope:** this repository only; no destructive rewrite, unrelated language migration, or implicit cross-repository execution is authorized.

## Purpose

Translate Anti-Teradayn into measurable controls: bounded responsibilities, explicit interfaces, predictable resource use, minimal necessary dependencies, and reproducible verification. “Typified steaming” means typed, bounded, reviewable changes—not a new runtime or a claim of zero entropy.

## Seven-phase protocol

1. **Dependency discipline.** Inventory dependencies and remove only demonstrably unnecessary components. Preserve product-required GUI, web, scripting, and network surfaces; isolate them from the core rather than deleting them.
2. **Corpuscular transparency.** Prefer explicit data flow, narrow functions, fixed-width ABI types, clear ownership, and measured hot paths. Use assembly only where profiling or platform requirements justify it. Swift is optional, not a universal bridge.
3. **Hardware boundaries.** Keep privileged and hardware-specific operations in native platform adapters with explicit contracts, errors, and capability checks. Ruby is optional tooling, not a kernel-driver ABI.
4. **Applicable validation.** Run the repository's actual unit, integration, static, build, and stress tests. GUI, Lua, rendering, interrupt, and hardware tests apply only where the product has those surfaces. Separate host, emulator, and physical-target evidence.
5. **Hardened integration.** Apply least privilege, bounded inputs/timeouts, authenticated transport where relevant, and explicit cache/retention rules. Google and other external services are optional, never assumed.
6. **SAMBU relationship.** Integrate SAMBU only for real statistical/scientific workloads and through versioned data contracts. Do not add irrelevant modeling dependencies.
7. **Resource allocation.** Keep core computation in the native implementation and orchestration in existing supported layers. C/C++/C#/Swift/Ruby are not mandatory tracks. Replace “six-molecule allocation” with measurable memory, CPU, concurrency, and latency budgets.

## Typed-steaming rules

- **Never boil:** no broad refactor without scoped behavior change and regression coverage.
- **Never over-boil:** keep modules bounded; prefer composition and explicit ownership.
- **Never cook:** avoid hidden global state, unbounded queues, implicit network calls, and unnecessary runtime work.
- Preserve public APIs unless a versioned migration is supplied.
- Make no performance claim without reproducible benchmark data.
- Host tests do not establish hardware or production readiness by themselves.

## Repository-specific application

**Verified profile:** compact C11 deterministic component lifecycle runtime with explicit states, caller-provided storage, init/step/shutdown callbacks, error propagation, recursion guards, and host tests. Preserve non-preemptive semantics and caller-owned scheduling. Focus on state-transition coverage, fault injection, callback reentrancy tests, and deterministic resource limits. Do not imply RTOS, interrupt scheduler, or MMIO support. Checks: `make test`; `python one.py check`.

## Acceptance checklist

- [ ] Scope and intended behavior are explicit.
- [ ] Dependency/security impact is recorded; no blanket technology purge.
- [ ] ABI, ownership, error handling, and resource limits are documented.
- [ ] Relevant tests and checks pass; unsupported target checks remain marked pending.
- [ ] Documentation matches code and does not overstate capabilities.
- [ ] Cross-repository links use versioned contracts and do not execute foreign code.

## Ecosystem boundary

Repositories remain independently buildable with their own APIs, release cycles, and test evidence. Federation means documented contracts, not a forced monolith. See the [Hellduck Integration Playbook](https://github.com/bboroski/Hellduck/blob/main/docs/INTEGRATION_PLAYBOOK.md) where applicable.

---

*Make every claim testable, every boundary explicit, and every optimization measurable.*
