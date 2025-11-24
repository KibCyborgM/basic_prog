#include "menu.hpp"
#include "menu_functions.hpp"

#include <iostream>

int main() {	
	tar::MenuItem study_summ = {"1 - Хочу научиться складывать!", tar::study_summ};
	tar::MenuItem study_substract = {"2 - Хочу научиться вычитать!", tar::study_substract};
	tar::MenuItem study_multiply = {"3 - Хочу научиться умножать!", tar::study_multiply};
	tar::MenuItem study_divide = {"4 - Хочу научиться делить!", tar::study_divide};
	tar::MenuItem study_go_back = {"0 - Вернуться в главное меню", tar::study_go_back};
	
	tar::MenuItem* study_children[] {
		&study_go_back,
		&study_summ,
		&study_substract,
		&study_multiply,
		&study_divide
	};
	
	const int study_size = sizeof(study_children) / sizeof(study_children[0]);
	
	tar::MenuItem study = {"1 - Хочу учиться математике!", tar::show_menu, study_children, study_size};
	tar::MenuItem exit = {"0 - Я лучше пойду полежу...", tar::exit};
	
	tar::MenuItem* main_children[] = {&exit, &study};
	const int main_size = sizeof(main_children) / sizeof(main_children[0]);
	
	tar::MenuItem main {nullptr, tar::show_menu, main_children, main_size};
	
	study.parent = &main;
	exit.parent = &main;
	
	study_summ.parent = &study;
	study_substract.parent = &study;
	study_divide.parent = &study;
	study_multiply.parent = &study;
	study_go_back.parent = &study;
	
	int user_input;
	
	const tar::MenuItem* current = &main;
	do {
		current = current->func(current);
	} while(true);
}