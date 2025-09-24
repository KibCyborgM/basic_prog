#include "sortings.hpp"
#include <vector>

void biv::sortings::shall_sort(std::vector<int>& a, std::vector<long> gl) {
    int n = a.size();
    int h;
    for (int i = gl.size()-1; i >= 0; --i){
        h = gl[i];
        for (int c = h; c < n; ++c){
            int temp = a[c];
            int j = c;
            for (; j >= h && a[j-h] > temp; j -= h) a[j] = a[j-h];
            a[j] = temp;
        }
        
    }

}