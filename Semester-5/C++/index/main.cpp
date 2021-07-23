#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>

struct NOTE {
	char name[2];
	int pos;
	int len;
};


void create_index(const char* fname, char* str) {
	FILE* index = fopen(fname, "w+b");
	char* ptr1 = strchr(str, '#'), * ptr2;
	while ( (ptr2 = strchr(ptr1 + 1, '#')) != NULL ) {
		NOTE note;
		note.name[0] = *(ptr1 + 1); note.name[1] = *(ptr1 + 2);
		note.pos = ptr1 - str + 3;
		note.len = ptr2 - ptr1 - 3;
		//printf("%c %c %d %d\n", note.name[0], note.name[1], note.pos, note.len);
		fwrite(&note, sizeof(NOTE), 1, index);
		ptr1 = ptr2;
	}
	fclose(index);
}



std::pair<int, int> get_index(const char* fname, const char* str_name) {
	FILE* index = fopen(fname, "rb");
	NOTE buff;
	while (fread(&buff, sizeof(NOTE), 1, index) == 1) {
		//printf("%c%c %d %d\n", buff.name[0], buff.name[1], buff.pos, buff.len);
		if (buff.name[0] == str_name[0] && buff.name[1] == str_name[1]) {
			fclose(index);
			return { buff.pos, buff.len };
		}
	}
	fclose(index);
	return { -1, -1 };
}

char* get_str(const char* str_name, const char* fname = "input.txt", const char* index_file = "index.txt") {
	std::pair<int, int> index = get_index(index_file, str_name);
	if (index.first == -1) return NULL;
	
	FILE* data = fopen(fname, "r");
	fseek(data, index.first, SEEK_SET);
	char* ans = new char[index.second + 1];
	fgets(ans, index.second + 1, data);
	fclose(data);

	return ans;
}

bool change_substr(const char* str_name, const char* new_str, const char* fname = "input.txt", const char* index_file = "index.txt") {
	std::pair<int, int> index = get_index(index_file, str_name);
	if (index.first == -1) return false;

	FILE* data = fopen(fname, "r+");
	fseek(data, index.first, SEEK_SET);
	char* str = new char[index.second + 1];
	fgets(str, index.second + 1, data);
	fseek(data, index.first, SEEK_SET);
	//std::cout << str << "\n";

	strncpy(str, new_str, index.second);
	if (strlen(new_str) < index.second) {
		for (int i = strlen(new_str); i < index.second; ++i)
			str[i] = ' ';
	}
	//std::cout << str << "\n";
	fprintf(data, "%s", str);
	fclose(data);
	return 0;
}

int main(int argc, char* argv[]) {
	printf("%s\n", argv[0]);
	FILE* input = (argc > 1) ? fopen(argv[1], "r") : stdin;
	char* str = new char[200];
	fgets(str, 200, input);
	printf("%s\n", str);
	fclose(input);

	//making index file
	create_index("index.txt", str);
	FILE* index = fopen("index.txt", "r+b");
	
	//printing information from index file
	fseek(index, 0, SEEK_SET);
	NOTE buff;
	while (fread(&buff, sizeof(NOTE), 1, index) == 1) {
		printf("%c%c %d %d\n", buff.name[0], buff.name[1], buff.pos, buff.len);
	}
	fclose(index);

	std::cout << "lt: " << get_str("lt") << "\n\n";
	
	std::cout << "Old pt: " << get_str("pt") << "\n";
	char new_str1[] = "brawngp2";
	change_substr("pt", new_str1);
	std::cout << "Changed pt: " << get_str("pt") << "\n\n";

	std::cout << "Old tt: " << get_str("tt") << "\n";
	char new_str2[] = "f1";
	change_substr("tt", new_str2);
	std::cout << "Changed tt: " << get_str("tt") << "\n";

	system("pause");
	return 0;
}