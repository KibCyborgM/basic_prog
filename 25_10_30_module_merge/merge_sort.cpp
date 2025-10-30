#include "merge.hpp"
#include "merge_sort.hpp"

void tar::merge_sort(int* const arr, const int l, const int r) {
	if (l >= r){ 
		return;
	}
    int len = r-l + 1;
    
	int c = (l+r) / 2;
	tar::merge_sort(arr, l, c);
	tar::merge_sort(arr, c+1, r);
	tar::merge(arr, l, c, r);
    
}