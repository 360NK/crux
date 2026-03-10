#include <vector>
#include "analyzer.hpp"
#include "graph.hpp"
#include "scheduler.hpp"
#include <algorithm>
#include <chrono>

AnalysisReport analyze(const TaskGraph& g, const std::vector<ExecutionRecord>& records) {
    int n = g.nodes.size();

    std::vector<long> dp(n,0);
    for (int i : g.topo_order) {
        dp[i] = g.nodes[i].duration_ms;
        for (int pred : g.nodes[i].deps) {
            dp[i] = std::max(dp[i], dp[pred] + (long)g.nodes[i].duration_ms);
        }
    }

    long cp_ms = *std::max_element(dp.begin(), dp.end());

    std::vector<int> cp_path;
    int cur = (int)(std::max_element(dp.begin(), dp.end()) - dp.begin());
    while (true) {
        cp_path.push_back(cur);
        int next = -1;
        for (int pred : g.nodes[cur].deps) {
            if (dp[pred] == dp[cur] - g.nodes[cur].duration_ms) {
                next = pred;
                break;
            }
        }
        if (next == -1) break;
        cur = next;
    }
    std::reverse(cp_path.begin(), cp_path.end());

    std::vector<bool> on_cp(n, false);
    for (int idx : cp_path) on_cp[idx] = true;

    std::vector<TaskAnalysis> tasks(n);
    for (int i = 0; i < n; i++) {
        tasks[i].task_index = i;
        tasks[i].on_critical_path = on_cp[i];
        tasks[i].critical_path_distance_ms = dp[i];

        if (g.nodes[i].deps.empty()) {
            tasks[i].wait_time_ms = 0;
        } else {
            auto latest_pred_end = records[g.nodes[i].deps[0]].end_time;
            for (int pred : g.nodes[i].deps) {
                if (records[pred].end_time > latest_pred_end) {
                    latest_pred_end = records[pred].end_time;
                }
            }
            auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(records[i].start_time - latest_pred_end).count();
            tasks[i].wait_time_ms = std::max(0LL, diff);
        }
    }
    return AnalysisReport{cp_path, cp_ms, tasks};
}
