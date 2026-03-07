#include "../src/graph.hpp"
#include <iostream>
#include <cassert>

int main() {
    TaskGraph g;
    std::string err;

    bool loaded = load_graph("../examples/simple_pipeline.json", g, err);
    if (!loaded) {
        std::cerr << "Failed to load graph: " << err << "\n";
    }
    assert(loaded);
    assert(g.nodes.size() == 6);

    int ingest_idx = g.id_to_index["ingest"];
    assert(g.nodes[ingest_idx].deps.empty());

    TaskGraph bad;
    std::string bad_err;
    assert(!load_graph("examples/cyclic_graph.json", bad, bad_err));
    assert(!bad_err.empty());

    std::cout << "Graph tests passed.\n";
    return 0;
}