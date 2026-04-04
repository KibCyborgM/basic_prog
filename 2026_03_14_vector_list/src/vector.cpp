#include "vector.hpp"

#include <iostream>

using tar::Vector;

template<typename T>
const std::size_t Vector<T>::START_CAPACITY = 8;

template<typename T>
Vector<T>::Vector() {
	arr = new T[capacity];
}

template<typename T>
Vector<T>::~Vector() {
	delete[] arr;
	arr = nullptr;
	capacity = START_CAPACITY;
	size = 0;
}



template<typename T>
std::size_t Vector<T>::get_size() const noexcept {
	return size;
}

template<typename T>
bool Vector<T>::has_item(const T& value) const noexcept {
	for (std::size_t i = 0; i < size; i++){
		if (arr[i] == value)
			return true;
	}
	
	return false;
}

template<typename T>
bool Vector<T>::insert(const std::size_t position, const T& value) {
	if (position > size)
		return false;
	
	
	if (size >= capacity){
		double_capacity(position, value);
		size++;
		return true;
	} else {
	

		for (std::size_t i = size; i > position; i--)
			arr[i] = arr[i-1];
		arr[position] = value;
		size += 1;
		return true;
	}
}

template<typename T>
void Vector<T>::print() const noexcept {
    std::cout << "[";
    for (std::size_t i = 0; i < size; i++) {
        std::cout << arr[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]";
}

template<typename T>
void Vector<T>::push_back(const T& value) {
	if (size >= capacity){
		double_capacity(size, value);
	}
	arr[size] = value;
	size++;
}

template<typename T>
bool Vector<T>::remove_first(const T& value) {
	
	if (size > 0){
		if (size < capacity/2){
		T* new_arr = new T[capacity/2];
		for (std::size_t i = 0; i < size; i++)
			new_arr[i] = arr[i];
		delete[] arr;
		arr = new_arr;
	}
		
		std::size_t deleted = 0;
		for (; deleted < size; deleted++){
			if (arr[deleted] == value)
					break;
		}
		
		if (deleted == size)
			return false;
		
		arr[deleted] = 0;
		T* new_arr = new T[capacity];
		for (std::size_t i = 0; i < deleted; i++)
			new_arr[i] = arr[i];
		for (std::size_t i = deleted + 1; i < size; i++)
			new_arr[i-1] = arr[i];
		delete[] arr;
		arr = new_arr;
		size -= 1;
		
		return true;
	}
	
	return false;
}

template<typename T>
void Vector<T>::double_capacity(const std::size_t insertion_position, const T& value){
	capacity *= 2;
	T* new_arr = new T[capacity];
	if (arr != nullptr){
		for (std::size_t i = 0; i < insertion_position; i++)
			new_arr[i] = arr[i];
		new_arr[insertion_position] = value;
		for (std::size_t i = insertion_position + 1; i < size+1; i++)
			new_arr[i] = arr[i];
		
	}
	delete[] arr;
	arr = new_arr;
}