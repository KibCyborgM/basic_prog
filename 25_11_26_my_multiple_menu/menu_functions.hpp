#pragma once

#include "menu.hpp"


namespace tar {
	const MenuItem* show_menu(const MenuItem* current);
	
	const MenuItem* main_exit(const MenuItem* current);
	
	const MenuItem* go_back(const MenuItem* current);
	
	const MenuItem* prog_languages(const MenuItem* current);
	const MenuItem* prog_algs_and_structures(const MenuItem* current);
	
	const MenuItem* others_databases(const MenuItem* current);
	const MenuItem* others_multiprog(const MenuItem* current);
	const MenuItem* others_network(const MenuItem* current);
}