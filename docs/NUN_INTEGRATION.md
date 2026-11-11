# NUN integration — deterministic component lifecycle

## Assigned responsibility

CO provides a small C11 runtime for deterministic component initialization, stepping, fault transition and shutdown. Its NUN role is lifecycle management for future system components or services after the kernel can create and supervise execution contexts.

## Current verified state

- The runtime uses caller-owned storage and does not require a heap.
- Component callbacks return explicit statuses.
- Lifecycle states and recursion guards are covered by host tests.
- CO does not implement CPU scheduling, preemption, interrupt dispatch, process isolation or kernel IPC.

## Integration contract

1. Keep lifecycle callbacks deterministic, bounded and explicit about failure.
2. Do not call component lifecycle callbacks directly from interrupt context. IRQ handlers should publish bounded events for a later execution context.
3. Do not claim a component is isolated merely because CO tracks its state.
4. Make ownership of callback context and backing memory explicit; reject invalid sizes and state transitions.
5. Bind CO to a NUN service/process contract only after the kernel's scheduler and IPC contracts exist.
6. Preserve host tests and add target tests for any architecture-specific integration.

## Dependency order

[NUN](https://github.com/bboroski/NUN) must first pass QEMU boot, memory and interrupt checkpoints. CO may then supervise services in a supported runtime context; it is not a substitute for the kernel scheduler or init process.

## ABI status

No CO public ABI is changed here. No NUN syscall or process ABI is frozen. Record future NUN-facing changes in `CHANGELOG.NUN`.
