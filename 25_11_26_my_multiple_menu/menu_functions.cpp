#include <iostream>

#include "menu_functions.hpp"

const tar::MenuItem* tar::show_menu(const MenuItem* current){
	std::cout << "Обучайка приветствует тебя!" << std::endl;
	for (int i = 1; i < current->children_size; i ++){
		std::cout << current->children[i]->title << std::endl;
	}
	std::cout << current->children[0]->title << std::endl;
	std::cout << "Обучайка >";
	
	int user_input;
	std::cin >> user_input;
	std::cout << std::endl;
	
	return current->children[user_input];
}

const tar::MenuItem* tar::main_exit(const MenuItem* current){
	std::exit(0);
}

const tar::MenuItem* tar::go_back(const MenuItem* current){
	return current->parent->parent;
}


const tar::MenuItem* tar::prog_languages(const MenuItem* current){
	std::cout << current->title << "\n" << std::endl;
	return current-> parent;
}
const tar::MenuItem* tar::prog_algs_and_structures(const MenuItem* current){
	std::cout << current->title << "\n" << std::endl;
	return current-> parent;
}

const tar::MenuItem* tar::others_databases(const MenuItem* current){
	std::cout << current->title << "\n" << std::endl;
	return current-> parent;
}
const tar::MenuItem* tar::others_multiprog(const MenuItem* current){
	std::cout << current->title << "\n" << std::endl;
	return current-> parent;
}
const tar::MenuItem* tar::others_network(const MenuItem* current){
	std::cout << current->title << "\n" << std::endl;
	return current-> parent;
}