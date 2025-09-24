#include <vector>
#include "generate_numbers.hpp"
#include <algorithm>


void biv::generate::generate_3gl (std::vector<long>& gl, int n) {
	for (int i = 1; i <= n; i *= 2) {       // степени двойки
        for (int j = 1; i * j <= n; j *= 3) { // степени тройки
            gl.push_back(i * j);
        }
    }
    std::sort(gl.begin(), gl.end());
}