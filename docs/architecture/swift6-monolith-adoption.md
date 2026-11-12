# Swift 6+ Modular-Monolith Adoption Contract

**Status:** architecture baseline; implementation is incremental and must be proven by repository CI. **Language mode:** Swift 6; pin the exact toolchain.

## Objective and safety rules

Use an in-process Swift core only where the product target supports it. Use SwiftPM targets with acyclic dependencies and typed APIs. Preserve independently deployed, hardware, privilege, network, and fault-containment boundaries.

- Enable Swift 6 language mode and complete strict-concurrency checking per target; fix diagnostics rather than blanket-suppressing them.
- Protect shared mutable state with actors or narrow synchronization. Audit every `@unchecked Sendable`, unsafe pointer, native bridge, and mutable global.
- `Sendable` is a checked concurrency contract, not a module-access restriction. Keep non-Sendable values in their owning isolation domain.
- Prefer value semantics; use `~Copyable`, `borrowing`, and `consuming` only when supported by the pinned compiler and justified by measurements.
- Partition SwiftPM targets into Domain, Application, Infrastructure, Adapters, and Tests; avoid cyclic dependencies and global service locators.
- Replace only unnecessary in-process HTTP/JSON hops with typed calls. Keep device, process, network, privilege, and fault-containment boundaries.
- Preserve APIs, ABI, schemas, file formats, and cross-language contracts. Version incompatible changes and test old/new compatibility.
- Select embedded or external persistence from durability and multi-writer needs; test transactions, WAL/checkpointing, crash recovery, backup, and restore.
- Shutdown by stopping ingress, cancelling owned task groups, draining owned transports, flushing durable state, and reporting incomplete cleanup.
- Benchmark real workloads (toolchain, hardware, p50/p95/p99, throughput, allocations, memory) before optimization; do not claim theoretical latency as measured.
- Enable CMO/LTO only in supported release configurations after correctness and reproducibility checks.
- CI must pin toolchains, build with strict concurrency, test native boundaries, and validate supported targets.

## Adoption gates

A. Inventory languages, deployables, module graph, public interfaces, persistence, unsafe code, and target constraints.  
B. Define the smallest stable Swift core API and versioned contracts at genuine process boundaries.  
C. Migrate target-by-target to Swift 6 complete concurrency checking.  
D. Isolate C/C++ with Clang modules or a narrow C ABI when direct interop is unsuitable; test ownership and error propagation.  
E. Select storage from durability/multi-writer needs and implement orderly lifecycle.  
F. Profile before selectively enabling LTO/CMO.  
G. Merge only after required CI, ABI checks, and review pass.

## Repository-specific scope

CO owns deterministic component lifecycle and platform adapters. Preserve deterministic lifecycle semantics, adapter contracts, and platform-specific isolation; any Swift core must prove deterministic startup/shutdown and versioned compatibility.



This document is an adoption contract, not a claim that Swift code or a SwiftPM package already exists. Preserve this repository's native platform and lifecycle contracts. Swift components must be additive, versioned, and tested against existing consumers.

## Acceptance criteria

- Pinned toolchain and reproducible SwiftPM build for each Swift target.
- Complete strict-concurrency checks with no unexplained suppressions.
- Tests for isolation, cancellation, persistence recovery, and native-boundary ownership where applicable.
- Documented module/deployment graph and versioned external contracts.
- Benchmarks and CI evidence attached to implementation PRs.
