#pragma once
#include "menu.hpp"

namespace tar{
	const tar::MenuItem* show_menu(const MenuItem* current);
	
	const tar::MenuItem* exit(const MenuItem* current);
	
	const tar::MenuItem* study_go_back(const MenuItem* current);
	const tar::MenuItem* study_summ(const MenuItem* current);
	const tar::MenuItem* study_substract(const MenuItem* current);
	const tar::MenuItem* study_multiply(const MenuItem* current);
	const tar::MenuItem* study_divide(const MenuItem* current);
};