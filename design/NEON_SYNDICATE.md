# NEON SYNDICATE — interface and visual specification

**Repository:** CO  
**Project focus:** C RUNTIME / DEPENDENCY BOUNDARIES / PLATFORM SERVICES  
**Visual category:** C RUNTIME LIBRARY / ARCHITECTURE VISUAL

## Brand foundation
NEON SYNDICATE is an original cyber-noir visual system built around precise technical information, industrial geometry and restrained neon. It draws on broad cyberpunk aesthetics, without copying protected game artwork, logos or UI assets.

## Color tokens
- Void Black `#050505` — canvas and deep contrast.
- Warning Yellow `#FCEE0A` — primary actions, selection and high-priority attention.
- System Red `#FF003C` — critical errors and blocked states.
- Data Blue `#00F0FF` — links, technical highlights and informational signals.
- Interface White `#FFFFFF` — primary text.
- Carbon surfaces `#0D1115` / `#11171C`; muted text `#A6B2BC`.

Pair semantic colors with labels or icons. Red is reserved for critical states; cyan is informational.

## Typography and layout
Use Orbitron or Rajdhani for uppercase headings, Rajdhani/system sans-serif for body text and Roboto Mono/Share Tech Mono for code, IDs and measurements. Prefer asymmetrical grids, thin structural rules, readable data panels, chamfered corners and restrained hexagonal textures. Provide local font fallbacks.

## Effects, motion and accessibility
Use edge glows sparingly, transitions from 120–260 ms and subtle hover elevation. Glitch effects must never obscure labels, data, errors or focus. Respect `prefers-reduced-motion`. Keep visible keyboard focus, 40 px minimum controls and 44 px touch targets. Never communicate state by color alone.

## Project-specific focus
C RUNTIME / DEPENDENCY BOUNDARIES / PLATFORM SERVICES

- RUNTIME CORE
- DEPENDENCY GRAPH
- PLATFORM ADAPTERS
- Reference flow: DECLARE → RESOLVE → EXECUTE → VERIFY

The SVG is a project-specific presentation/architecture concept. It does not assert that a GUI exists or that all visual modules are implemented.

## Screenshot policy
Capture actual runtime screenshots from a running application at a stated viewport. Prefer 1920×1080 or higher and retain a 1366×768 compact view where relevant. Use PNG/WebP for actual captures, label synthetic data and remove personal paths or secrets. The 1920×1200 SVG is a vector design preview, not a screenshot.

## Files
- `assets/neon-syndicate/overview.svg` — project-specific visual concept.
- `assets/neon-syndicate/theme.css` — reusable web theme layer.
- `design/neon-syndicate.tokens.json` — machine-readable design tokens.
