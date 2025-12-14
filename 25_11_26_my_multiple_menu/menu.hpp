# pragma once

namespace tar {
	struct MenuItem {
		const char* const title;  // 1 МС (8Б)
		const MenuItem* (*func)(const MenuItem* current); // 1 МС (8Б)
		
		const MenuItem* parent; //1 МС (8Б)
		
		const MenuItem* const *children; //1 МС (8Б)
		bool t1; // 1 Б
		const int children_size; // 4 Б
		
	}; // 40 Б!
}; 