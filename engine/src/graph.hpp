#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct TaskNode {
    int index;
    std::string id;
    int duration_ms;
    std::vector<int> deps;
    std::vector<int> outs;
};

struct TaskGraph {
    std::string name;
    int num_workers;
    std::vector<TaskNode> nodes;
    std::vector<int> indegree;
    std::vector<int> topo_order;
    std::unordered_map<std::string, int> id_to_index;
};

bool load_graph(const std::string& path, TaskGraph& out, std::string& err);
