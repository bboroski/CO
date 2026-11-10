# NUN Mesh integration — CO

CO owns deterministic component lifecycle: initialization, one bounded step per poll, fault retention and cleanup. Its portable state machine remains independent of any OS, hardware register map or health policy.

## Mesh connections

- **Kloz:** an application may place a validated Kloz platform-ops pointer in callback context. CO itself does not call MMIO or require Kloz.
- **SaintSI:** call the optional bridge after a successful start and after each completed poll. A faulted runtime deliberately stops refreshing its heartbeat so the observer can report staleness.
- **ReaperCripple:** a Reaper bootstrap stage may own a CO runtime as a component service; cleanup must remain explicit and reverse-ordered.
- **Klipot:** the portal lists the contract and offers a state-machine simulation; that simulation is not this C runtime.

## Integration boundary

The optional header include/co/saintsi_bridge.h requires both include roots on the consumer's include path. It does not change the core library or build flags. The host application supplies the timebase in SaintSI ticks and decides what a degraded result means.

See the [mesh protocol](https://github.com/bboroski/Klipot/blob/main/docs/INTEGRATION_PROTOCOL.md) and [SaintSI](https://github.com/bboroski/SaintSI).
