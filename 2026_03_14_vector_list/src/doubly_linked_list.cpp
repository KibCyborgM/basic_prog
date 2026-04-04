#include "doubly_linked_list.hpp"

#include <iostream>

using tar::DoublyLinkedList;

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node* current = begin;
	while (current != nullptr) {
		Node* next = current->next;
		delete current;
		current = next;
	}
}

template<typename T>
std::size_t DoublyLinkedList<T>::get_size() const noexcept {
	Node* current_node = begin;
	if (current_node == nullptr)
		return 0;
	std::size_t size = 1;
	while (current_node != end){
		current_node = current_node->next;
		size += 1;
	}
	
	return size;
}

template<typename T>
bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
    Node* current_node = begin;
    
    while (current_node != nullptr) {
        if (current_node->value == value) {
            return true;
        }
        current_node = current_node->next;
    }
    
    return false;
}

template<typename T>
void DoublyLinkedList<T>::print() const noexcept {
	if (this->get_size() == 0){
		std::cout << "Empty" << std::endl;
		return;
	}
	std::cout << "[";
	Node* current_node = begin;
	while (current_node->next != nullptr){
		std::cout << current_node->value << " <-> ";
		current_node = current_node->next;
	}
	std::cout << current_node->value << "]" << std::endl;
	
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
	Node* new_node = new Node(value);
	if (begin == nullptr)
		this->begin = new_node;
	else{
		new_node->prev = end;
		this->end->next = new_node;
	}
	this->end = new_node;
}

template<typename T>
bool DoublyLinkedList<T>::remove_first(const T& value) noexcept {
	Node* current_node = begin;
	
	while (current_node != nullptr) {
		if (current_node->value == value) {
			break;
		}
		current_node = current_node->next;
	}
	
	if (current_node == nullptr) {
		return false;
	}
	
	if (current_node->prev != nullptr) {
		current_node->prev->next = current_node->next;
	} else {
		begin = current_node->next;
	}
	
	if (current_node->next != nullptr) {
		current_node->next->prev = current_node->prev;
	} else {
		end = current_node->prev;
	}
	
	delete current_node;
	
	
	return true;
}