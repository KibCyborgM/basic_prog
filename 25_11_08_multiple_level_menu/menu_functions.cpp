#include "menu_functions.hpp"

#include <cstdlib>
#include <iostream>

const tar::MenuItem* tar::exit(const MenuItem* current){
	std::exit(0);
}

const tar::MenuItem* tar::show_menu(const MenuItem* current) {
	std::cout << "Обучайка приветствует тебя!" << std::endl;
	for (int i = 1; i < current->children_count; i++) {
		std::cout << current->children[i]->title << std::endl;
	}
	std::cout << current->children[0]->title << std::endl;		
	std::cout << "Обучайка > ";
	
	int user_input;
	std::cin >> user_input;
	std::cout << std::endl;
	
	return current->children[user_input];
}
const tar::MenuItem* tar::study_go_back(const MenuItem* current){
	return current->parent->parent;
	
}
const tar::MenuItem* tar::study_summ(const MenuItem* current){
	std::cout << current->title << std::endl;
	return current->parent;
}
const tar::MenuItem* tar::study_substract(const MenuItem* current){
	std::cout << current->title << std::endl;
	return current->parent;
}
const tar::MenuItem* tar::study_multiply(const MenuItem* current){
	std::cout << current->title << std::endl;
	return current->parent;
}
const tar::MenuItem* tar::study_divide(const MenuItem* current){
	std::cout << current->title << std::endl;
	return current->parent;
}