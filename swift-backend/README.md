# CO Server-Side Swift backend

A separately deployable Swift 6 / Vapor service boundary. It complements existing project components and does not replace their native, language, runtime, or system responsibilities.

Run with `cd swift-backend && swift test && swift run co-server`.

Configuration: `HOST`, `PORT`, `SERVICE_NAME`, `SERVICE_VERSION`. Secrets must come from a deployment secret provider and must never be committed.

Endpoints: `GET /health`, `GET /ready`, `GET /v1/health`. Readiness currently checks only process readiness, not database or external dependency health. Trace ID response propagation is enabled.

The core provides immutable Sendable request context, validated Codable configuration, API error DTOs, an async repository contract and trace/security-header middleware. Repository implementations must use bounded connection pools, parameterized SQL and service-level transaction boundaries.

Production gates not yet claimed as complete: PostgreSQL/Redis providers, JWT/RBAC, TLS termination, OpenTelemetry, Prometheus, migrations, rate limiting, OpenAPI generation, load testing and Kubernetes deployment.
