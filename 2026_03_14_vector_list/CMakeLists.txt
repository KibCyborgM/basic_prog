cmake_minimum_required(VERSION 3.14)

project(containers)

set(CONTAINERS_LIB "containers_lib")
add_library(${CONTAINERS_LIB} "")

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)
enable_testing()
add_subdirectory(test)