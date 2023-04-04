#ifndef LIB_H
#define LIB_H

void Delete(int** array, int n);
bool split(char* type_str, char** type_ArrayOfStr, int n=3);
int convert_StrToNumber(char* str);
bool ParseString(int* type_array, char* type_str, char sep='/');

#endif // LIB_H