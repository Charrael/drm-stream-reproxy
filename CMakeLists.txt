cmake_minimum_required(VERSION 3.30.5)
project(drm-stream-reproxy)

find_package(pugixml REQUIRED) 
find_package(CURL REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} pugixml::pugixml CURL::libcurl )