cmake_minimum_required(VERSION 3.25)

project(parallelism
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Eigen3 3.4 REQUIRED)

add_executable(main
    src/main.cpp
)
target_link_libraries(main
    Eigen3::Eigen
)

install(
    TARGETS
        main
    EXPORT
        ParallelismTargets
    ARCHIVE
    LIBRARY
    RUNTIME
)

install(
    EXPORT
        ParallelismTargets
    DESTINATION
        lib/cmake
    NAMESPACE
        parallelism::
)
