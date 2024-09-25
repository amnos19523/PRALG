cmake_minimum_required(VERSION 3.10)
project(project_name)
find_package(Imagine REQUIRED COMPONENTS Graphics)
add_executable(nom_de_exe test.cpp)
target_link_libraries(ImagineGraphicsTest Imagine::Graphics)

