# CO bounded event history

This project receives an allocation-free fixed-capacity ledger for event/fault evidence. Records hold a monotonic sequence and timestamp, event/source codes, severity, confidence annotation, evidence flags and an optional reference to an earlier sequence. The ring evicts the oldest record on overflow and counts drops with saturation.

The API captures metadata only: no raw private payloads, clock calls, I/O or device mutation. Corroboration must include an observed signal; confidence is not a probability of truth. Read operations return an ordered snapshot without changing runtime state.

CI compiles the contract tests with strict warnings.
