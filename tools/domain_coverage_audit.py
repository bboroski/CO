#!/usr/bin/env python3
"""Validate the 13-area engineering profile and its repository evidence."""
from __future__ import annotations

import argparse
import json
from pathlib import Path
from typing import Any

DOMAINS = {
    "architecture_governance": ("Architecture and governance", "Identity, policy, invariants, and technical decision records."),
    "data_quality": ("Data quality", "Input validation, bounded data, cleanup, and corruption containment."),
    "dependency_orchestration": ("Dependency orchestration", "Module graphs, event flow, sequencing, and state transitions."),
    "platform_interoperability": ("Platform interoperability", "Versioned APIs, ABI contracts, adapters, and cross-target boundaries."),
    "developer_automation": ("Developer automation", "CLI tools, generators, repeatable workflows, and productivity tooling."),
    "resource_governance": ("Resource governance", "Memory, CPU, storage, capacity, budgets, and allocation limits."),
    "fault_resilience": ("Fault resilience", "Error paths, rollback, isolation, recovery, and fail-safe behavior."),
    "provenance_integrity": ("Provenance and integrity", "Evidence, checksums, manifests, traceability, and change accountability."),
    "engineering_knowledge": ("Engineering knowledge", "Schemas, specifications, static analysis, and technical documentation."),
    "build_execution": ("Build and execution", "Build systems, runtime entry points, launch, packaging, and execution."),
    "release_governance": ("Release governance", "CI, quality gates, versioning, reproducible releases, and audit policy."),
    "interface_observability": ("Interface and observability", "Developer interfaces, logs, reports, diagnostics, and visualization."),
    "testing_qualification": ("Testing and qualification", "Tests, fuzzing, health checks, timeouts, and target qualification."),
}
STATUSES = {"implemented", "partial", "planned"}
RELATIONS = {"adapter", "contract", "metadata", "optional", "planned"}


def read_json(path: Path) -> dict[str, Any]:
    try:
        value = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, UnicodeError, json.JSONDecodeError) as exc:
        raise ValueError(f"cannot read {path}: {exc}") from exc
    if not isinstance(value, dict):
        raise ValueError(f"{path} must contain a JSON object")
    return value


def audit(repo: Path, ecosystem_root: Path | None = None) -> dict[str, Any]:
    repo = repo.resolve()
    issues: list[str] = []
    try:
        profile = read_json(repo / "engineering.domains.json")
    except ValueError as exc:
        return {"repository": str(repo), "ok": False, "issues": [str(exc)], "domains": []}

    if profile.get("schema_version") != 1:
        issues.append("schema_version must be 1")
    repository = profile.get("repository")
    if not isinstance(repository, str) or len(repository.split("/")) != 2 or not all(repository.split("/")):
        issues.append("repository must use canonical owner/name form")
        repository = str(repository or repo.name)

    module_path = repo / "sambu.module.json"
    if module_path.is_file():
        try:
            module = read_json(module_path)
            declared = module.get("repository")
            if declared and declared != repository:
                issues.append(f"sambu.module.json repository mismatch: {declared} != {repository}")
        except ValueError as exc:
            issues.append(str(exc))

    definitions = profile.get("domains")
    if not isinstance(definitions, dict):
        definitions = {}
        issues.append("domains must be a JSON object keyed by domain id")
    extra, missing = sorted(set(definitions) - set(DOMAINS)), sorted(set(DOMAINS) - set(definitions))
    if extra:
        issues.append("unknown domains: " + ", ".join(extra))
    if missing:
        issues.append("missing domains: " + ", ".join(missing))

    rows: list[dict[str, Any]] = []
    for domain_id, (title, purpose) in DOMAINS.items():
        item = definitions.get(domain_id, {})
        if not isinstance(item, dict):
            item = {}
            issues.append(f"{domain_id}: definition must be an object")
        status = item.get("status", "planned")
        if not isinstance(status, str) or status not in STATUSES:
            issues.append(f"{domain_id}: invalid status {status!r}")
            status = "planned"
        evidence = item.get("evidence", [])
        if not isinstance(evidence, list) or not all(isinstance(x, str) and x for x in evidence):
            issues.append(f"{domain_id}: evidence must be a list of relative paths")
            evidence = []
        present: list[str] = []
        for raw in evidence:
            path = Path(raw)
            if path.is_absolute() or ".." in path.parts:
                issues.append(f"{domain_id}: unsafe evidence path {raw!r}")
            elif (repo / path).exists():
                present.append(raw)
            else:
                issues.append(f"{domain_id}: evidence path does not exist: {raw}")
        if status == "implemented" and not present:
            issues.append(f"{domain_id}: implemented requires at least one existing evidence path")
        rows.append({"id": domain_id, "title": title, "purpose": purpose, "status": status,
                     "evidence": present, "evidence_count": len(present)})

    integrations = profile.get("integrations", [])
    if not isinstance(integrations, list):
        issues.append("integrations must be a list")
        integrations = []
    seen: set[str] = set()
    peer_rows: list[dict[str, Any]] = []
    for item in integrations:
        if not isinstance(item, dict):
            issues.append("each integration must be an object")
            continue
        target, relation, state = item.get("repository"), item.get("relation"), item.get("status")
        if not isinstance(target, str) or len(target.split("/")) != 2 or not all(target.split("/")):
            issues.append(f"integration has invalid repository: {target!r}")
            continue
        if target in seen:
            issues.append(f"duplicate integration: {target}")
        seen.add(target)
        if not isinstance(relation, str) or relation not in RELATIONS:
            issues.append(f"{target}: invalid integration relation {relation!r}")
        if not isinstance(state, str) or state not in STATUSES:
            issues.append(f"{target}: invalid integration status {state!r}")
        found = None
        if ecosystem_root is not None:
            found = (ecosystem_root.resolve() / target.split("/", 1)[1]).is_dir()
            if not found:
                issues.append(f"{target}: not found under ecosystem root {ecosystem_root}")
        peer_rows.append({"repository": target, "relation": relation, "status": state,
                          "workspace_present": found})

    counts = {state: sum(1 for row in rows if row["status"] == state) for state in STATUSES}
    return {"repository": repository, "role": profile.get("role", "unspecified"),
            "maturity": profile.get("maturity", "unspecified"), "ok": not issues,
            "counts": counts, "integrations": peer_rows, "domains": rows, "issues": issues}


def audit_workspace(root: Path) -> dict[str, Any]:
    reports = [audit(path, root) for path in sorted(root.iterdir())
               if path.is_dir() and (path / "engineering.domains.json").is_file()]
    return {"ok": bool(reports) and all(item["ok"] for item in reports), "repositories": reports}


def render(report: dict[str, Any], output_format: str) -> str:
    if output_format == "json":
        return json.dumps(report, ensure_ascii=False, indent=2)
    if "repositories" in report:
        if output_format == "markdown":
            return "\n\n".join(render(item, "markdown") for item in report["repositories"])
        return "\n".join(render(item, "table") for item in report["repositories"])
    if output_format == "markdown":
        lines = [f"# Engineering Domain Coverage — {report['repository']}", "",
                 f"- **Result:** {'PASS' if report['ok'] else 'FAIL'}",
                 f"- **Role:** {report.get('role', 'unspecified')}",
                 f"- **Maturity:** {report.get('maturity', 'unspecified')}", "",
                 "| Engineering area | Status | Evidence |", "|---|---|---|"]
        for row in report.get("domains", []):
            lines.append(f"| {row['id']} — {row['title']} | {row['status']} | {', '.join(row['evidence']) or '—'} |")
        if report.get("issues"):
            lines += ["", "## Findings"] + [f"- {item}" for item in report["issues"]]
        return "\n".join(lines)
    counts = report.get("counts", {})
    lines = [f"{report['repository']}  {'PASS' if report['ok'] else 'FAIL'}",
             f"implemented={counts.get('implemented', 0)}  partial={counts.get('partial', 0)}  planned={counts.get('planned', 0)}"]
    lines += [f"  {row['id']:<28} {row['status']:<11} {row['title']}" for row in report.get("domains", [])]
    lines += [f"ERROR: {item}" for item in report.get("issues", [])]
    return "\n".join(lines)


def self_test() -> int:
    import tempfile
    with tempfile.TemporaryDirectory() as temp:
        root = Path(temp)
        (root / "docs").mkdir()
        (root / "docs/policy.md").write_text("policy", encoding="utf-8")
        profile = {"schema_version": 1, "repository": "example/demo", "role": "self-test",
                   "domains": {key: {"status": "planned", "evidence": []} for key in DOMAINS}}
        profile["domains"]["architecture_governance"] = {
            "status": "implemented", "evidence": ["docs/policy.md"]}
        target = root / "engineering.domains.json"
        target.write_text(json.dumps(profile), encoding="utf-8")
        assert audit(root)["ok"]
        profile["domains"]["architecture_governance"]["evidence"] = ["docs/missing.md"]
        target.write_text(json.dumps(profile), encoding="utf-8")
        assert not audit(root)["ok"]
    print("Engineering Domain Coverage self-test: PASS")
    return 0


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Validate the 13-area engineering profile and its evidence.")
    parser.add_argument("--repo", type=Path, default=Path.cwd(), help="repository root")
    parser.add_argument("--ecosystem-root", type=Path, help="directory containing sibling repositories")
    parser.add_argument("--all", action="store_true", help="audit all direct child repositories under --ecosystem-root")
    parser.add_argument("--format", choices=("table", "markdown", "json"), default="table")
    parser.add_argument("--self-test", action="store_true", help="run dependency-free internal tests")
    args = parser.parse_args(argv)
    if args.self_test:
        return self_test()
    report = audit_workspace(args.ecosystem_root) if args.all and args.ecosystem_root else audit(args.repo, args.ecosystem_root)
    print(render(report, args.format))
    return 0 if report.get("ok") else 1


if __name__ == "__main__":
    raise SystemExit(main())
