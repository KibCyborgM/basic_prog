# pragma once

namespace tar {
	struct MenuItem {
		const char* const title;
		const char* const message;
		
		const MenuItem* (*func)(const MenuItem* current);
		
		const MenuItem* parent;
		
		const MenuItem* const *children; 
		const int children_size;
	};
}; 