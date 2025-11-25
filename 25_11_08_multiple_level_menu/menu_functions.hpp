#pragma once
#include "menu.hpp"

namespace tar{
	const tar::MenuItem* show_menu(const MenuItem* current);
	
	const tar::MenuItem* exit(const MenuItem* current);
	
	const tar::MenuItem* go_back(const MenuItem* current);
	const tar::MenuItem* algebra_summ(const MenuItem* current);
	const tar::MenuItem* algebra_substract(const MenuItem* current);
	const tar::MenuItem* algebra_multiply(const MenuItem* current);
	const tar::MenuItem* algebra_divide(const MenuItem* current);
	
	const tar::MenuItem* mathanalysis_dif_count(const MenuItem* current);
	const tar::MenuItem* mathanalysis_int_count(const MenuItem* current);
};