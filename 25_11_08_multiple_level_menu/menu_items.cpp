#include "menu_items.hpp"
#include "menu_functions.hpp"

#include <cstddef>

const tar::MenuItem tar::ALGEBRA_SUMM = {
	"1 - Хочу научиться складывать!", tar::algebra_summ, &tar::ALGEBRA
};
const tar::MenuItem tar::ALGEBRA_SUBSTRACT = {
	"2 - Хочу научиться вычитать!", tar::algebra_substract, &tar::ALGEBRA
};
const tar::MenuItem tar::ALGEBRA_MULTIPLY = {
	"3 - Хочу научиться умножать!", tar::algebra_multiply, &tar::ALGEBRA
};
const tar::MenuItem tar::ALGEBRA_DIVIDE = {
	"4 - Хочу научиться делить!", tar::algebra_divide, &tar::ALGEBRA
};
const tar::MenuItem tar::ALGEBRA_GO_BACK = {
	"0 - Вернуться к выбору предметов.", tar::go_back, &tar::ALGEBRA
};

const tar::MenuItem tar::MATHANALYSIS_DIF_COUNT {
	"1 - Хочу изучить дифференциальное исчисление!", tar::mathanalysis_dif_count, &tar::MATHANALYSIS
};
const tar::MenuItem tar::MATHANALYSIS_INT_COUNT {
	"2 - Хочу изучить интегральное исчисление!", tar::mathanalysis_int_count, &tar::MATHANALYSIS
};
const tar:: MenuItem tar::MATHANALYSIS_GO_BACK {
	"0 - Вернуться к выбору предметов.", tar::go_back, &tar::MATHANALYSIS
};

namespace {
	const tar::MenuItem* const algebra_children[] = {
		&tar::ALGEBRA_GO_BACK,
		&tar::ALGEBRA_SUMM,
		&tar::ALGEBRA_SUBSTRACT,
		&tar::ALGEBRA_MULTIPLY,
		&tar::ALGEBRA_DIVIDE
	};
	const int algebra_size = sizeof(algebra_children) / sizeof(algebra_children[0]);
	
	const tar::MenuItem* const mathanalysis_children[] = {
		&tar::MATHANALYSIS_GO_BACK,
		&tar::MATHANALYSIS_DIF_COUNT,
		&tar::MATHANALYSIS_INT_COUNT
	};
	const int mathanalysis_size = sizeof(mathanalysis_children) / sizeof(mathanalysis_children[0]);
}

const tar::MenuItem tar::STUDY_GO_BACK = {
	"0 - Вернуться в главное меню.", tar::go_back, &tar::STUDY
};

const tar::MenuItem tar::ALGEBRA = {
	"1 - Хочу изучать алгебру!", tar::show_menu, &tar::STUDY, algebra_children, algebra_size
};

const tar::MenuItem tar:: MATHANALYSIS {
	"2 - Хочу изучать математический анализ!", tar::show_menu, &tar::STUDY, mathanalysis_children, mathanalysis_size
};

namespace {
	const tar::MenuItem* const study_children[] = {
		&tar::STUDY_GO_BACK,
		&tar::ALGEBRA,
		&tar::MATHANALYSIS
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