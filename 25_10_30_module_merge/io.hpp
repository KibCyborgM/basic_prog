#ifndef IO_HPP
#define IO_HPP

namespace tar {
	namespace prints {
		void print_arr(int* const arr, const int arr_len);
		void print_text(const char* text);
	}
	namespace insertions {
		void insert_arr(int* arr, const int arr_len);
	}
}

#endif