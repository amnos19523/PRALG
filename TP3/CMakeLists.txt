cmake_minimum_required(VERSION 3.10)
project(STL)

if(LINUX)
        find_package(Imagine REQUIRED COMPONENTS Graphics)
	add_executable(TP3 main.cpp)
	target_link_libraries(TP2 Imagine::Graphics)
else()
        set(QT_DIR "C:/ENPC/5.15.2/mingw81_64/lib/cmake/Qt5")
        set(Qt5_DIR "C:/ENPC/5.15.2/mingw81_64/lib/cmake/Qt5")
        find_package(Imagine REQUIRED COMPONENTS Graphics)
        add_executable(TP2 main.cpp)
        target_link_libraries(TP2 main.cpp)
endif()
