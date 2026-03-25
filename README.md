# Crux

Crux is a C++17 DAG scheduling project built to explore how dependency graphs can be parsed, validated, analyzed and prepared for execution.

The current implementation focuses on:
- parsing task graphs from JSON
- validating acyclicity using Kahn's algorithm
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
- topological validation with Kahn's algorithm
- critical path analysis
- structured reporting / analysis components

Planned / future work:
- parallel task execution
- thread-pool based scheduling
- richer runtime metrics
- benchmark comparisons across graph shapes (chain, diamond, fan-out)

Note: `num_workers` is parsed from the graph JSON but parallel execution is not yet implemented. All tasks currently run sequentially on worker 0.
