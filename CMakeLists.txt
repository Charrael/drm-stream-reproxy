cmake_minimum_required(VERSION 3.31.6)
project(drm-stream-reproxy)

find_package(pugixml REQUIRED) 
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} pugixml::pugixml CURL::libcurl nlohmann_json::nlohmann_json)