# Crux

Crux is a C++17 DAG scheduling project built to explore how dependency graphs can be parsed, validated, analyzed and prepared for execution.

The current implementation focuses on:
- parsing task graphs from JSON
- validating acyclicity using Kahn’s algorithm
- building dependency and successor relationships
- computing critical path information with dynamic programming
- producing structured execution and analysis output

This project is part of my broader interest in runtimes, schedulers, and performance-oriented backend systems.
---

## Current status

Implemented:
- JSON graph parsing
- dependency graph construction
- indegree tracking
- topological validation with Kahn’s algorithm
- critical path analysis
- structured reporting / analysis components

Planned / future work:
- parallel task execution
- thread-pool based scheduling
- richer runtime metrics
- stronger benchmarking
- optional AI-assisted report interpretation

---

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
cd build/engine && ./crux
```

Example output:
```
ingest — 200ms
validate — 155ms
transform — 303ms
enrich — 250ms
merge — 103ms
load — 55ms
```

---

## Why this project exists

I built Crux to better understand the mechanics behind graph-based execution systems:
- how DAG workloads are represented
- how dependency order is enforced
- how critical work can be identified
- how runtime design choices affect execution behavior

It is a learning and systems-design project, not just a finished end-user tool.

---

## License

MIT — see [LICENSE](LICENSE)
