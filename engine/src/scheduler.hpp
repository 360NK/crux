#pragma once
#include <chrono>
#include <vector>
#include "graph.hpp"

struct ExecutionRecord {
    int task_index;
    int worker_id;
    std::chrono::steady_clock::time_point start_time;
    std::chrono::steady_clock::time_point end_time;
};

class Scheduler {
public:
    explicit Scheduler(const TaskGraph& graph);
    std::vector<ExecutionRecord> run_sequential();

private:
    const TaskGraph& graph_;
    std::vector<ExecutionRecord> records_;
};
