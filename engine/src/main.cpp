#include "graph.hpp"
#include "scheduler.hpp"
#include "analyzer.hpp"
#include "reporter.hpp"
#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "usage: crux <graph.json>\n";
        return 1;
    }
    std::string path = argv[1];

    TaskGraph g;
    std::string err;

    if (!load_graph(path, g, err)) {
        std::cerr << "Error: " << err << "\n";
        return 1;
    }

    Scheduler s(g);

    auto t_start = std::chrono::steady_clock::now();
    auto records = s.run_sequential();
    auto t_end = std::chrono::steady_clock::now();

    long wall_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();

    auto report = analyze(g, records);
    std::string output_path = "reports/" + g.name + "_report.json";
    
    std::filesystem::create_directories("reports");
    write_report(g, records, report, wall_time_ms, output_path);
    std::cout << "Report written to " << output_path << "\n";

    return 0;
}
