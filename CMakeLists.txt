cmake_minimum_required(VERSION 3.17)
project(search_engine2)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json) 


add_executable(search_engine2 src/main.cpp src/ConverterJSON.cpp include/ConverterJSON.h src/InvertedIndex.cpp include/InvertedIndex.h src/SearchServer.cpp include/SearchServer.h)

target_link_libraries(search_engine2 PRIVATE nlohmann_json::nlohmann_json)
target_link_options(search_engine2 PRIVATE -static-libgcc -static-libstdc++)
