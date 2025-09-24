#include "generate_numbers.hpp"
#include "sortings.hpp"
#include "io.hpp"
#include <vector>
#include <iostream>

int main(){
	std::vector<long> gl;
	biv::generate::generate_3gl(gl, 20);
	
	std::vector<int> a = {5, 10, 2, 83, 20, 94, 230, 10, 43, 51, 52,  5, 84, 4456, 66, 78, 45, 78, 91, 20};
	
	biv::print_array("Массив до сортировки:", a);
	
	biv::sortings::shall_sort(a, gl);
	
	biv::print_array("Массив после сортировки:", a);
	
	

}
