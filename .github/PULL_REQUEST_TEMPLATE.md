## Summary
- [ ] Describe the change and acceptance criteria.
- [ ] Preserve canonical CO names, public C API and `co_` prefix.

## Lifecycle behavior / limitation → verified capability
- Constraint and evidence:
- Implemented behavior:
- Remaining host/application responsibility:

## Documentation and UI
- [ ] README and affected UA/EN/RU variants are current.
- [ ] Host UI follows `docs/gui/GUI_DESIGN_STANDARD.md`.
- [ ] No GUI/runtime behavior is claimed unless implemented.
- [ ] Wireframes are labelled; screenshots come from runnable host software.

## Verification
- [ ] `make test` and relevant CI pass.
- [ ] Lifecycle, partial-init cleanup, fault retention and reentrancy checked.
- [ ] Changed code meets 80% coverage where configured or exception justified.
- [ ] Callback ordering, caller-owned memory and concurrency assumptions documented.
- [ ] Compatibility and error paths reviewed.

## Review policy
- Branches: `feature/<ticket>-<slug>`, `fix/<slug>`, `docs/<slug>`.
- No direct commits to protected default/release branches.
- Merge requires two independent approvals and all required CI checks; branch protection must enforce this.
- [ ] Two independent approvals.
- [ ] Required CI checks all green.

## Українська / Русский
- [ ] README та локалізації актуальні.
- [ ] Життєвий цикл, callback safety, пам'ять і повторний вхід перевірені.
- [ ] Для злиття є два незалежні схвалення та успішний CI.
