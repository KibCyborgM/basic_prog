project(merge_test)

set(LIBRARY "merge_sort_lib666")

add_library(${LIBRARY} "")

add_subdirectory(src)
add_subdirectory(test)