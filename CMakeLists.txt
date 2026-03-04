include(FetchContent)
FetchContent_Declare(
  nlohmann_json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp
  DOWNLOAD_NO_EXTRACT TRUE
  DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/engine/include/nlohmann
)
FetchContent_MakeAvailable(nlohmann_json)
