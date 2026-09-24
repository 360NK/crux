#include "../src/graph.hpp"
#include <iostream>
#include <string>

// Unlike assert(), this still runs when NDEBUG is defined (Release builds).
static int failures = 0;
static void check(bool cond, const char* what) {
    if (!cond) {
        std::cerr << "FAIL: " << what << "\n";
        ++failures;
    }
}

int main() {
    TaskGraph g;
    std::string err;

    bool loaded = load_graph(examples + "/simple_pipeline.json", g, err);
    if (!loaded) std::cerr << "load error: " << err << "\n";
    check(loaded, "simple_pipeline.json loads");
    check(g.nodes.size() == 6, "simple_pipeline has 6 tasks");
    check(g.nodes[g.id_to_index["ingest"]].deps.empty(), "ingest has no deps");

    TaskGraph bad;
    std::string bad_err;
    bool bad_loaded = load_graph(examples + "/cyclic_graph.json", bad, bad_err);
    check(!bad_loaded, "cyclic_graph.json is rejected");
    check(!bad_err.empty(), "cyclic graph produces an error message");
 
    if (failures > 0) {
        std::cerr << failures << " check(s) failed.\n";
        return 1;
    }
    std::cout << "Graph tests passed.\n";
    return 0;

}