#include <iostream>
#include <cstring>
#include <iomanip>

#include "exception.h"

void Delete(char** array, int n=3) {
	for (int i = 0; i < n; ++i) {
			delete[] array[i];
		}
	delete[] array;
}

int ToNumber(const char* str) {
	return atoi(str);
}

bool ParseString(int* type_array, char* type_str, char sep='/') {
//array consist of strings ( array like {{"1543"}, {"179"}, {"57"}	)
	int n=3;
	char** ArrayOfStr = new char* [n];
	for (int i = 0 ; i < n; ++i) {
		ArrayOfStr[i] = new char[5];
	}

//	seperate_ind  - array with index where seperating index is
	int* seperate_ind = new int[n];
	int place=-1; // index [0, L-1]
	int L = strlen(type_str);
	type_str[L] = sep;
	if (L > 10) {
		Delete(ArrayOfStr);
		delete[] seperate_ind;
		throw InvalidArgument("Invalid Argument: too much symbols in the string!");
	}
	for (int i = 0; type_str[i]; ++i) {
		if (type_str[i] == sep) {
			if (++place > 2) {
				Delete(ArrayOfStr);
				delete[] seperate_ind;
				throw InvalidArgument("Invalid Argument: seperate symbols are more than 2!");
			}
			seperate_ind[place] = i;
		}
	}

	if (place == -1 || place == 0 || place == 1) {
		throw InvalidArgument();
	}

//	fill the ArrayOfStr with Str(Str like "1234")
	int start = 0;
	place = 0;
	int end = seperate_ind[place];
	for (int j = 0; j < n; ++j) {
		for (int i = start; i < end; ++i) {
			ArrayOfStr[j][i-start] = type_str[i];
		}
		start = end+1;
		end = seperate_ind[++place];
	}
	delete[] seperate_ind;

//	convert str to numbers in array
	for (int i = 0; i < n; ++i) {
		type_array[i] = ToNumber(ArrayOfStr[i]);
	}

	Delete(ArrayOfStr, n);
	return true;
}