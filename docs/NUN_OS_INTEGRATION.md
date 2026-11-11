# NUN OS integration contract — CO

## Ownership
CO owns the component/object lifecycle and service composition model. NUN owns kernel IPC primitives, process isolation, handles, capabilities and syscall dispatch. CO components execute above the kernel boundary and must not assume kernel privilege.

## Integration direction
1. Specify stable component identity, interface version, lifecycle state and dependency metadata.
2. Map component activation/deactivation to NUN service-manager and IPC contracts when those exist.
3. Make object references and service handles capability-scoped; never treat a component name as authorization.
4. Define deterministic startup ordering, cancellation and teardown behavior.
5. Keep lifecycle tests runnable on the host without a NUN kernel.

## Acceptance gates
- Lifecycle transitions are deterministic and tested for failure, timeout and repeated calls.
- Service interfaces carry explicit version information.
- Invalid or unauthorized handles fail closed.
- Kernel IPC integration is tested through a versioned adapter, not private kernel structures.

## Current status
CO provides the user-space component model. The current QEMU bring-up kernel has no process model or IPC syscall ABI, so direct kernel integration remains a later phase.
