# Crux — DAG Task Scheduler with AI Bottleneck Analysis

A C++17 parallel task scheduler that models workflows as directed acyclic
graphs, executes them across a thread pool, and produces a structured
execution report. A Python AI agent then reads the report and explains
bottlenecks in plain English using Anthropic's tool-calling API.

Built from scratch as a deep dive into graph algorithms, concurrent systems,
and AI integration.

---

## Current Status

| Component | Status |
|---|---|
| JSON graph loading + Kahn's topological sort | Done |
| Cycle detection | Done |
| Sequential scheduler | Done |
| Execution records (per-task timestamps) | Done |
| Reporter (JSON output) | Not started |
| Critical path analyzer | Not started |
| Parallel scheduler + thread pool | Not started |
| Python AI agent | Not started |

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

## What It Will Do

- Parses JSON task graphs and validates them for cycles using Kahn's algorithm
- Computes the critical path using dynamic programming on the DAG
- Executes tasks in dependency order across a configurable thread pool
- Measures per-task wait times, worker utilization, and parallelism efficiency
- Generates a structured JSON execution report
- Feeds the report to an AI agent that calls structured tools to explain
  which tasks caused delays and why

---

## License

MIT — see [LICENSE](LICENSE)
