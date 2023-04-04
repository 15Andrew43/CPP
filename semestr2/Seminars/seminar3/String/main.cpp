#include <iostream>

#include "string.h"

#include "exception.h"

int main() {
//	char* a = new char [10];
//	std::cin >> a;
//	String name=a;
//	std::cout << name[2];
	/*
	std::cout << "------------------------\n";

	String s1("Andrew");
	std::cout << s1[1];

	std::cout << "------------------------\n";

	String s2("Kolya", 100);
	std::cout << s2[0];

	String s3(12, 'p');
	std::cout << s3[0];

	std::cout << "------------------------\n";

	String s4;
	s4 = "friiiendly";
	String s5;
	s5 = s4;
	std::cout << s4[0] << '\n';
	std::cout << s5[0] << '\n';

	std::cout << s4.Size() << '\n';
	std::cout << s5.Size() << '\n';

	std::cout << s4.Capacity() << '\n';
	std::cout << s5.Capacity() << '\n';

	std::cout << "-------------------\n";
	s4.Resize(30, 'a');	

	std::cout << s4[10] << '\n';
	std::cout << s4.Empty() << '\n';

	std::cout << "------------------------\n";


	String s6 = "qwertyuiop";
//	String s7 = "mmmmmmmmmmaaaaammmmmaaaaa";

	s6 += "mmmmmmmmmmaaaaammmmmaaaaa";

	std::cout << s6[15] << '\n';
	
	String s7 = "puma";
	s6+='t';
	std::cout << s6[4] << '\n';


	std::cout << "00000000000000000000000000000000000000000000000\n";
*/
	String z1;
	std::cin >> z1;
	try {
		std::cout << z1.Back() << '\n';
	} catch (Exception& ex) {
		std::cout << ex.what() << '\n';
	}
	String z2 = "";
	try {
		z2.PopBack();
		std::cout << z2;
	} catch (Exception& ex) {
		std::cout << ex.what() << '\n';
	}
}
