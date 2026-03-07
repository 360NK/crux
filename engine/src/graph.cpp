#include "graph.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <queue>
#include <iostream>

using json = nlohmann::json;

bool run_kahns(TaskGraph& g, std::string& err) {
    std::vector<int> work_indegree = g.indegree;

    std::queue<int> qu;
    for (int i = 0; i < (int)g.nodes.size(); i++) {
        if (work_indegree[i] == 0) {
            qu.push(i);
        }
    }

    g.topo_order.clear();

    while (!qu.empty()) {
        int cur = qu.front();
        qu.pop();
        g.topo_order.push_back(cur);
        for (int out : g.nodes[cur].outs) {
            work_indegree[out]--;
            if (work_indegree[out] == 0) {
                qu.push(out);
            }
        }
    }

    if ((int)g.topo_order.size() != (int)g.nodes.size()) {
        err = "Cycle detected in task graph.";
        return false;
    }
    return true;
}

bool load_graph(const std::string& path, TaskGraph& out, std::string& err) {
    std::ifstream f(path);
    if (!f.is_open()) {
        err = "Could not open file: " + path;
        return false;
    }

    json j;
    try {
        f >> j;
    } catch (json::parse_error& e) {
        err = std::string("JSON Parse error: ") + e.what();
        return false;
    }

    out.name = j.value("graph_name", "UnnamedGraph");
    out.num_workers = j.value("num_workers", 1);

    int current_index = 0;
    for (const auto& item : j["tasks"]) {
        TaskNode node;
        node.id = item["id"];
        node.duration_ms = item["duration_ms"];
        node.index = current_index;

        out.nodes.push_back(node);
        out.id_to_index[node.id] = current_index;
        current_index++;
    }

    out.indegree.resize(out.nodes.size(), 0);

    for (const auto& item : j["tasks"]) {
        std::string current_id = item["id"];
        int current_idx = out.id_to_index[current_id];

        if (item.contains("deps")) {
            for (const auto& dep_id : item["deps"]) {
                if (out.id_to_index.find(dep_id) == out.id_to_index.end()) {
                    err = "Unknown dpendency ID: " + dep_id.get<std::string>();
                    return false;
                }
                int dep_idx = out.id_to_index[dep_id];
                
                out.nodes[current_idx].deps.push_back(dep_idx);
                out.nodes[dep_idx].outs.push_back(current_idx);
                out.indegree[current_idx]++;
            }
        }
    }

    return run_kahns(out, err);
}
