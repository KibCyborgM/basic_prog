#include "menu_items.hpp"
#include "menu_functions.hpp"

const tar::MenuItem tar::OTHERS_DATABASES = {
	"1 - Базы данных", tar::others_databases, &tar::PROG_OTHERS
};
const tar::MenuItem tar::OTHERS_MULTIPROG = {
	"2 - Многопоточное программирование", tar::others_multiprog, &tar::PROG_OTHERS
};
const tar::MenuItem tar::OTHERS_NETWORK = {
	"3 - Сетевые технологии", tar::others_network, &tar::PROG_OTHERS
};
const tar::MenuItem tar::OTHERS_GO_BACK = {
	"0 - Выйти в предыдущее меню", tar::go_back, &tar::PROG_OTHERS
};

namespace {
	const tar::MenuItem* const others_children[] = {
		&tar::OTHERS_GO_BACK,
		&tar::OTHERS_DATABASES,
		&tar::OTHERS_MULTIPROG,
		&tar::OTHERS_NETWORK
	};
	
	const int others_children_size = sizeof(others_children) / sizeof(others_children[0]);
}

const tar::MenuItem tar::PROG_LANGUAGES = {
	"1 - Изучать языки программирования", tar::prog_languages, &tar::PROGRAMMING
};
const tar::MenuItem tar::PROG_ALGS_AND_STRUCTURES = {
	"2 - Алгоритмы и структуры", tar::prog_algs_and_structures, &tar::PROGRAMMING
};
const tar::MenuItem tar::PROG_OTHERS = {
	"3 - Другие технологии", tar::show_menu, &tar::PROGRAMMING, others_children, others_children_size
};
const tar::MenuItem tar::PROG_GO_BACK = {
	"0 - Выйти в главное меню", tar::go_back, &tar::PROGRAMMING
};

namespace {
	const tar::MenuItem* const prog_children[] = {
		&tar::PROG_GO_BACK,
		&tar::PROG_LANGUAGES,
		&tar::PROG_ALGS_AND_STRUCTURES,
		&tar::PROG_OTHERS
	};
	
	const int prog_children_size = sizeof(prog_children) / sizeof(prog_children[0]);
}

const tar::MenuItem tar::PROGRAMMING = {
	"1 - Изучать программирование", tar::show_menu, &tar::MAIN, prog_children, prog_children_size
};
const tar::MenuItem tar::FOOTBALL = {
	"0 - Пойти играть в футбол", tar::main_exit, &tar::MAIN
};

namespace {
	const tar::MenuItem* const main_children[] = {
		&tar::FOOTBALL,
		&tar::PROGRAMMING
	};
	
	const int main_children_size = sizeof(main_children) / sizeof(main_children[0]);
}

const tar::MenuItem tar::MAIN = {
	nullptr, tar::show_menu, nullptr, main_children, main_children_size
};