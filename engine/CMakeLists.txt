# Header search path for nlohmann/json
include_directories(include src)

# The core engine library
add_library(crux_core src/graph.cpp src/scheduler.cpp)

add_executable(crux src/main.cpp)
target_link_libraries(crux crux_core)

# The Day 1 Test Executable
add_executable(test_graph tests/test_graph.cpp)
target_link_libraries(test_graph crux_core)