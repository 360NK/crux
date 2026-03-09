#include "scheduler.hpp"
#include <thread>
#include <chrono>

Scheduler::Scheduler(const TaskGraph& graph) : graph_(graph) {}

std::vector<ExecutionRecord> Scheduler::run_sequential() {
    records_.resize(graph_.nodes.size());

    for (int idx : graph_.topo_order) {
        auto start = std::chrono::steady_clock::now();
        std::this_thread::sleep_for(
            std::chrono::milliseconds(graph_.nodes[idx].duration_ms));
        auto end = std::chrono::steady_clock::now();

        records_[idx] = {idx, 0, start, end};
    }

    return records_;
}
