#include "header.h"
/*
int symbol_counter(char* str, char symbol) {
	int ans = 0;
	for (; *str; ++str)
		if (*str == symbol) ++ans;
	return ans;
}*/



void modify(char* str, int& dot_counter, int& comma_counter) {
	dot_counter = 0;
	comma_counter = 0;

	bool fl = true;
	for (; *str; ++str, fl = !fl) {
		if (*str == '.') {
			++dot_counter;
			if (fl)
				*str = ',';
		}
		else if (*str == ',') {
			++comma_counter;
			if(fl) 
				*str = '.';
		}
	}
}

void modify_str(char* str, int& dot_counter, int& comma_counter) {
	dot_counter = 0;
	comma_counter = 0;
	char symbols[] = ".,";

	for (char *ptr = str; ptr = strpbrk(ptr, symbols); ++ptr) {
		if (*ptr == '.')  ++dot_counter; 
		if (*ptr == ',') ++comma_counter;

		unsigned int i = ptr - str;
		if (!(i&1)) {
			if (*ptr == '.') *ptr = ',';
			else
				if (*ptr == ',') *ptr = '.';
		}
	}
}

int reminder(unsigned int x, short degree) {
	unsigned int y = 0;
	return (x & ~((~y) << degree));
}