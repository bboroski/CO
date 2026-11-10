# CO operator surface

A browser-based visual inspector for the existing CO library. This is an optional operator/developer design, not a GUI embedded into the freestanding C11 core.

## Design interpretation

The shared abstract composition becomes a connected domain field: an operator view of explicit lifecycle states, one-step polling and bounded cleanup. It uses product-specific colours and information density rather than repeating another app's dashboard.

## Preview

Open `index.html` in a modern browser. No build tool or external JavaScript framework is required.

## Boundaries

All values are synthetic. The inspector does not invoke the C library, access hardware, drive actuators, validate a physical board or create assurance evidence. Host and target qualification remain separate.
