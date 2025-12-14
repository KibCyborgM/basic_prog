#include <iostream>

#include "io.hpp"
#include "merge_sort.hpp"


int main(){
	int arr_len;
	
	tar::print_text("Введите количество элементов:");
	std::cin >> arr_len;
	
	int* arr = new int[arr_len];
	
	tar::print_text("Введите элементы массива:");
	tar::insert_arr(arr, arr_len);
	
	tar::merge_sort(arr, 0, arr_len-1);
	
	tar::print_text("Ваш массив отсортирован:");
	tar::print_arr(arr, arr_len);
	
	

    delete[] arr;
    return 0;
}