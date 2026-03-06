project(long_numbers_tests)

set(LIBRARY "long_number_lib")

add_library(${LIBRARY} "")

add_subdirectory(src)
add_subdirectory(test)