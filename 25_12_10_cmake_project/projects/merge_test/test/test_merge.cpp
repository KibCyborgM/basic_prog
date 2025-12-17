#include <gtest/gtest.h>

#include "merge_sort.hpp"

TEST(ArraysEqual, AnyElementsCount) {
	int actual[] {9, 6, 7, 8, 1, 5, 3, 0, 4, 2};
	tar::merge_sort(actual, 0, 9);
	int expected[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	
	int ac_len = sizeof(actual)/sizeof(actual[0]);
	int ex_len = sizeof(expected)/sizeof(expected[0]);
	
	ASSERT_EQ(ex_len, ac_len)
		<< "Отсортированный массив и ожидаемый разных размеров";
	
	for(int i = 0; i < ac_len; i++) {
		ASSERT_EQ(expected[i], actual[i])
			<< "Ожидаемый и отсортированный массивы различаются элементом с индексовм: " << i;
		
	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}