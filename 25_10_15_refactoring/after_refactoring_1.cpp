#include <iostream>


float generate_arrays(int* const arr, const int size);

int main()
{
	const int len = 10;
	
	for (int i = 1; i <= 3; ++i){
		int array[len];
		float sum = 0;
		std::cout << "Последовательность №" << i << std::endl;
		sum = generate_arrays(array, len);
		float average_first = sum / len;
		std::cout << "Среднее последовательности №" << i << " = " << average_first << std::endl;
	}
    
    return 0;
}


float generate_arrays(int* const arr, const int len) {
	int sum;
	for (int i = 0; i < len; i++)
    {
        arr[i] = rand() % len;
        std::cout << arr[i] << ' ';
        sum = sum + arr[i];
    }
    std::cout << ' ' << std::endl;
	
	return sum;
}