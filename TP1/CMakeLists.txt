cmake_minimum_required(VERSION 3.10)
project(project_name)
find_package(Imagine REQUIRED COMPONENTS Graphics)
add_executable(TP1 main.cpp)
target_link_libraries(TP1 Imagine::Graphics)

