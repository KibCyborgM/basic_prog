target_sources(merge_sort
	PRIVATE
		io.cpp
		io.hpp
		merge_sort.cpp
		merge_sort.hpp
)

target_include_directories(merge_sort
	PRIVATE
		"${PROJECT_SOURCE_DIR}/merge_sort_src"
)