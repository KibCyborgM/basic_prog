#include "io.hpp"

#include <vector>
#include <iostream>

void biv::print_array(const char* comment, const std::vector<int> arr) {
	std::cout << comment << "\n";
	for (int x: arr) std::cout << x << " ";
	std::cout << "\n\n";
}
