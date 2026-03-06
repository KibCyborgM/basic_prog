set(SOURCES
	test_long_numbers.cpp
)

add_executable(test_long_numbers ${SOURCES})
target_link_libraries(test_long_numbers
	gtest_main
	${LIBRARY}
)

add_test(test_long_numbers test_long_numbers)