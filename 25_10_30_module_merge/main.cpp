#include "io.hpp"
#include "merge_sort.hpp"
#include<iostream>



int main(){
	int arr_len;
	
	tar::prints::print_text("Введите количество элементов:");
	std::cin >> arr_len;
	
	int* arr = new int[arr_len];
	
	tar::prints::print_text("Введите элементы массива:");
	tar::insertions::insert_arr(arr, arr_len);
	
	tar::merge_sort(arr, 0, arr_len-1);
	
	tar::prints::print_text("Ваш массив отсортирован:");
	tar::prints::print_arr(arr, arr_len);
	
	

    delete[] arr;
	arr = nullptr;
    return 0;
}