#include "menu_items.hpp"
#include "menu_functions.hpp"

#include <cstddef>

const tar::MenuItem tar::STUDY_SUMM = {
	"1 - Хочу научиться складывать!", tar::study_summ, &tar::STUDY
};
const tar::MenuItem tar::STUDY_SUBSTRACT = {
	"2 - Хочу научиться вычитать!", tar::study_substract, &tar::STUDY
};
const tar::MenuItem tar::STUDY_MULTIPLY = {
	"3 - Хочу научиться умножать!", tar::study_multiply, &tar::STUDY
};
const tar::MenuItem tar::STUDY_DIVIDE = {
	"4 - Хочу научиться делить!", tar::study_divide, &tar::STUDY
};
const tar::MenuItem tar::STUDY_GO_BACK = {
	"0 - Вернуться в главное меню", tar::study_go_back, &tar::STUDY
};

namespace {
	const tar::MenuItem* const study_children[] = {
		&tar::STUDY_GO_BACK,
		&tar::STUDY_SUMM,
		&tar::STUDY_SUBSTRACT,
		&tar::STUDY_MULTIPLY,
		&tar::STUDY_DIVIDE
	};
	const int study_size = sizeof(study_children) / sizeof(study_children[0]);
}

const tar::MenuItem tar::STUDY = {
	"1 - Хочу учиться математике!", tar::show_menu, &tar::MAIN, study_children, study_size
};

const tar::MenuItem tar::EXIT = {
	"0 - Я лучше пойду полежу...", tar::exit, &tar::MAIN
};

namespace {
	const tar::MenuItem* const main_children[] = {
		&tar::EXIT,
		&tar::STUDY
	};
	const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

const tar::MenuItem tar::MAIN = {
	nullptr, tar::show_menu, nullptr, main_children, main_size
};