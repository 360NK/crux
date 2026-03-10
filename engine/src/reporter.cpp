#include "reporter.hpp"
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void write_report(
    const TaskGraph& g, 
    const std::vector<ExecutionRecord>& records,
    const AnalysisReport& report,
    long wall_time_ms,
    const std::string& output_path
) {
    int n = (int)g.nodes.size();

    // earliest start across all records
    auto epoch = records[0].start_time;
    for (const auto& r : records) {
        if (r.start_time < epoch) epoch = r.start_time;
    }

    long declared_total_ms = 0;
    for (const auto& node : g.nodes) {
        declared_total_ms += node.duration_ms;
    }

    // parallelism's efficiency = declared total / (wall * workers)
    double efficiency = (g.num_workers > 0 && wall_time_ms > 0) ? (double)declared_total_ms / ((double)wall_time_ms * g.num_workers) : 0.0;

    // critical path as string ids
    json cp_ids = json::array();
    for (int idx : report.critical_path){
        cp_ids.push_back(g.nodes[idx].id);
    }

    // tasks arrays
    json tasks_arr = json::array();
    for (int i = 0; i < n; i++) {
        const auto& r = records[i];
        const auto& ta = report.tasks[i];
        long start_ms = std::chrono::duration_cast<std::chrono::milliseconds>(r.start_time - epoch).count();
        long end_ms = std::chrono::duration_cast<std::chrono::milliseconds>(r.end_time - epoch).count();
        tasks_arr.push_back({
            {"id", g.nodes[i].id},
            {"index", i},
            {"duration_ms", g.nodes[i].duration_ms},
            {"worker_id", r.worker_id},
            {"start_ms", start_ms},
            {"end_ms", end_ms},
            {"wait_time_ms", ta.wait_time_ms},
            {"on_critical_path", ta.on_critical_path}
        });
    }

    // aggregate active_ms per worker_id
    std::unordered_map<int, long> active_map;
    for (const auto& r : records) {
        long dur = std::chrono::duration_cast<std::chrono::milliseconds>(r.end_time - r.start_time).count();
        active_map[r.worker_id] += dur;
    }
    json workers_arr = json::array();
    for (auto& [wid, active_ms] : active_map) {
        long idle_ms = wall_time_ms - active_ms;
        double util = wall_time_ms > 0 ? (double)active_ms / wall_time_ms : 0.0;
        workers_arr.push_back({
            {"worker_id", wid},
            {"active_ms", active_ms},
            {"idle_ms", idle_ms},
            {"utilization", util}
        });
    }

    json out = {
        {"graph_name", g.name},
        {"num_workers", g.num_workers},
        {"wall_time_ms", wall_time_ms},
        {"declared_total_ms", declared_total_ms},
        {"parallelism_efficiency", efficiency},
        {"critical_path_ms", report.critical_path_ms},
        {"critical_path", cp_ids},
        {"tasks", tasks_arr},
        {"workers", workers_arr}
    };

    std::ofstream f(output_path);
    if (!f.is_open()) {
        throw std::runtime_error("write_report: cannot open " + output_path);
    }
    f << out.dump(2) << "\n";
}