#include "String.h"
#include <sstream>

int main(){

	char str[] = "Rama";
	String s(str);
	std::cout << "String(const char*) constructor\n" << s <<  "\ts.size(); " << s.size() << "\n";
	
	char* str2 = nullptr;
	String s3(str2);
	std::cout << "String(const char*) with nullptr size" << s3.size();

	String s1;
	std::cout << "default constructor\ns1.size(); " << s1.size() << "\n";
	
	String s2(s);
	std::cout << "Copy constructor String(s)\n" << s2 << "\ts2.size() " << s2.size() << "\n";


	String s4(String("Ramka"));
	std::cout << "Move constructor\ns4 " << s4 << "\tsize = " << s4.size() << "\n";

	String s5(std::move(s));
	std::cout << "Move constructor\ns5 " << s5 << "\tsize = " << s5.size() << "\n";

	std::cout << "Test operator[]. s5[1] before: " << s5[1] << "\n";
	s5[0] = 'K';
	std::cout << "s5[0] = 'K';\t" << s5 << "\n";

	s5 = s4;
	std::cout << "Test assignment operator: s5 = s4;\t" << s5 << "\n";

	s5 = String("Brawn GP");
	std::cout << "Move assignment operator: " << s5 << "\n";

	s5 = std::move(s4);
	std::cout << "Move assignment operator:" << s5 << "\n";

	s5 += String(" Lalalalala");
	std::cout << "+= operator. previous string += Lalalalala " << s5 << " " << s5.size() << "\n";
	
	std::cout << "() operator. s5(0, 3): " << s5(0, 3) << "\n";

	std::cout << "operator+ " << s5 + String(" wind") << "\n";

	std::cout << "aa==aa: " << (String("aa") == String("aa")) << "\n";
	std::cout << "aa<=aa: " << (String("aa") <= String("aa")) << "\n";
	std::cout << "aa > ab: " << (String("aa") > String("ab")) << "\n";

	std::stringstream st;
	st << "Bypass ratio\n";
	String s6;
	st >> s6 >> s5;
	std::cout << "operator>>: " << s6 <<  " " << s5 << "\n";
	
	const char* ptr = s6.c_str();
	std::cout << "c_str: " << *(ptr + 1) << "\n";

	std::cout << "Swap:\n";
	String s10("AA"), s11("BB");
	swap(s10, s11);
	std::cout << "swap('AA', 'BB'): " << s10 << " " << s11;
	return 0;
}

