cmake_minimum_required(VERSION 3.25)

project(parallelism
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(main
    src/main.cpp
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
