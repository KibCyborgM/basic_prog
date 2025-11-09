#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

namespace tar{
	void merge_sort(int* const arr, const int l, const int r);
	void merge(int* arr, const int left_ptr, const int center_ptr, const int right_ptr);
}
#endif