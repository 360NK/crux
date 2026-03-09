#include "graph.hpp"
#include "scheduler.hpp"
#include <iostream>

int main() {
    TaskGraph g;
    std::string err;

    if (!load_graph("../../examples/simple_pipeline.json", g, err)) {
        std::cerr << "Error: " << err << "\n";
        return 1;
    }

    Scheduler s(g);
    auto records = s.run_sequential();

    for (auto& r : records) {
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            r.end_time - r.start_time).count();
        std::cout << g.nodes[r.task_index].id << " — " << ms << "ms\n";
    }

    return 0;
}
