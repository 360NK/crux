#pragma once
#include <string>
#include <vector>
#include "graph.hpp"
#include "scheduler.hpp"
#include "analyzer.hpp"

void write_report(
    const TaskGraph& g,
    const std::vector<ExecutionRecord>& records,
    const AnalysisReport& report,
    long wall_time_ms,
    const std::string& output_path
);