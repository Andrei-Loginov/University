#pragma once
#include <cstdio>
#include <cstring>
#include <io.h>

void modify(char* str, int& dot_counter, int& comma_counter);
void modify_str(char* str, int& dot_counter, int& comma_counter);
bool file_exists(const char* fname);