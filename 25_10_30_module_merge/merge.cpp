#include "merge.hpp"

void tar::merge(int* arr, const int l, const int c, const int r) {
	int len_left = c - l + 1;
    int len_right = r - c;

    int* left_arr = new int[len_left];
    int* right_arr = new int[len_right];

    for (int i = 0; i < len_left; ++i){
		left_arr[i] = arr[l + i];
	}
    for (int j = 0; j < len_right; ++j){
		right_arr[j] = arr[c + 1 + j];
	}

    int i = 0, j = 0, k = l;
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