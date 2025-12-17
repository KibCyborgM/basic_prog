#include "merge_sort.hpp"

void tar::merge(int* arr, const int left_ptr, const int center_ptr, const int right_ptr) {
	int len_left = center_ptr - left_ptr + 1;
    int len_right = right_ptr - center_ptr;

    int* left_arr = new int[len_left];
    int* right_arr = new int[len_right];

    for (int i = 0; i < len_left; ++i){
		left_arr[i] = arr[left_ptr + i];
	}
    for (int j = 0; j < len_right; ++j){
		right_arr[j] = arr[center_ptr + 1 + j];
	}

    int i = 0, j = 0, k = left_ptr;
    while (i < len_left && j < len_right) {
        if (left_arr[i] <= right_arr[j]){
			arr[k++] = left_arr[i++];
		}
		
        else{
			arr[k++] = right_arr[j++];
		}
	}
	
    while (i < len_left){
		arr[k++] = left_arr[i++];
	}
	
    while (j < len_right){
		arr[k++] = right_arr[j++];
	}
	
	delete[] left_arr;
	delete[] right_arr;
	left_arr = nullptr;
	right_arr = nullptr;
}

void tar::merge_sort(int* const arr, const int left_ptr, const int right_ptr) { 
	if (left_ptr >= right_ptr){ 
		return;
	}
    int len = right_ptr - left_ptr + 1;
    
	int center_ptr = (left_ptr + right_ptr) / 2;
	tar::merge_sort(arr, left_ptr, center_ptr);
	tar::merge_sort(arr, center_ptr + 1, right_ptr);
	tar::merge(arr, left_ptr, center_ptr, right_ptr);
    
}