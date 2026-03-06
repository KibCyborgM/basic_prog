cmake_minimum_required(VERSION 3.2...3.27.5)

project(cmake_project)

add_subdirectory(lib/googletest)
enable_testing()


add_subdirectory(multiple_level_menu)
add_subdirectory(merge_sort)
add_subdirectory(merge_test)
add_subdirectory(long_numbers_tests)
add_subdirectory(long_numbers)

set(CMAKE_SUPPRESS_REGENERATION true)