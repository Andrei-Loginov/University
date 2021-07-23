#include "header.h"

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
			if (fl)
				*str = '.';
		}
	}
}

void modify_str(char* str, int& dot_counter, int& comma_counter) {
	dot_counter = 0;
	comma_counter = 0;
	char symbols[] = ".,";

	for (char* ptr = str; ptr = strpbrk(ptr, symbols); ++ptr) {
		if (*ptr == '.')  ++dot_counter;
		if (*ptr == ',') ++comma_counter;

		unsigned int i = ptr - str;
		if (!(i & 1)) {
			if (*ptr == '.') *ptr = ',';
			else
				if (*ptr == ',') *ptr = '.';
		}
	}
}
bool file_exists(const char* name) {
	return _access(name, 0) != -1;
}