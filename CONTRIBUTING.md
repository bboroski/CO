# Contributing to CO

CO owns runtime execution and diagnostic interfaces. Preserve the boundaries between runtime, diagnostics, dependency validation, and platform adapters; keep diagnostics deterministic and safe to run.

## Required workflow

1. Open or link an Issue and identify affected runtime, diagnostic, dependency, or platform contract.
2. Use a focused branch: `feat/<topic>`, `fix/<topic>`, `docs/<topic>`, or `security/<topic>`.
3. Keep public headers and runtime behavior backward-compatible unless a versioned change is documented.
4. Add tests for malformed input, failure paths, and platform-specific behavior.
5. Never commit credentials, production data, generated binaries, or local build output.

## Required validation

```bash
make clean test
CC=gcc make clean test
CC=clang make clean test
```

Run the ecosystem contract and domain validators relevant to the changed interfaces.

## Commits and releases

Use Conventional Commit subjects (`feat:`, `fix:`, `docs:`, `refactor:`, `perf:`, `test:`, `build:`, `ci:`, `chore:`). Breaking changes require `!:` and a `BREAKING CHANGE:` footer. Releases use SemVer; update changelog and migration notes before tagging.

## Pull request checklist

- State affected runtime/diagnostic contracts.
- Include exact compiler, test command, and result.
- Add tests for regressions and failure handling.
- Document changes to data formats, ABI, and compatibility.
