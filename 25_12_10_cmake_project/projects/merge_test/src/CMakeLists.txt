target_sources(${LIBRARY}
	PRIVATE
		merge_sort.cpp
	PUBLIC
		merge_sort.hpp
)


target_include_directories(${LIBRARY}
	PUBLIC
		"${PROJECT_SOURCE_DIR}/src"
)