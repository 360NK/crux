#pragma once
#include <vector>
#include "graph.hpp"
#include "scheduler.hpp"

struct TaskAnalysis {
    int task_index;
    long critical_path_distance_ms; // longest declared duration path from task to any sink
    long wait_time_ms; // actual_start - max(predecessor end times) ; 0 if no predecessors
    bool on_critical_path;
};

struct AnalysisReport {
    std::vector<int> critical_path; // ordered task indices
    long critical_path_ms;
    std::vector<TaskAnalysis> tasks;
};

AnalysisReport analyze(const TaskGraph& g, const std::vector<ExecutionRecord>& records);