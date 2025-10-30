#include "io.hpp"
#include<iostream>

void tar::prints::print_arr(int* const arr, const int arr_len){
	for(int i = 0; i < arr_len; i++){
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void tar::prints::print_text(const char* text){
	std::cout << text << std::endl;
}

void tar::insertions::insert_arr(int* arr, const int arr_len) {
	for (int i = 0; i < arr_len; i++){
		std::cin >> arr[i];
	}
}