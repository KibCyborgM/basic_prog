#include "menu.hpp"
#include "menu_functions.hpp"
#include "menu_items.hpp"

#include <iostream>

int main() {	
	const tar::MenuItem* current = &tar::MAIN;
	do {
		current = current->func(current);
	} while(true);
	
	return 0;
}