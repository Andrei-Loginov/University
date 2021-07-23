#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>

//allocates memory for arr_size char* 
void str_arr(char** &ptr, int arr_size){
	ptr = new char*[arr_size];
}

//deletes array of arr_size strings
void delete_array(char**& ptr, int arr_size) {
	for (int i = 0; i < arr_size; ++i)
		delete[]ptr[i];
	delete[]ptr;
	ptr = nullptr;
}

//copies source array into dest
void copy_arr(char** dest, char** source, int size) {
	for (int i = 0; i < size; ++i) {
		dest[i] = source[i];
	}
}

int main() {
	int size = 1, k = 0, multiplier = 2, str_length = 100;
	char** ptr1, ** ptr2, buff[100];
	ptr1 = new char* [size];

	while (strlen(fgets(buff, 100, stdin)) > 1) {
		ptr1[k] = new char[strlen(buff) + 1];
		strcpy(ptr1[k++], buff);
		if (k == size) {
			ptr2 = new char* [size * multiplier];
			copy_arr(ptr2, ptr1, size);
			delete[]ptr1;
			size *= multiplier;
			ptr1 = ptr2;
		}
	}

	for (int i = 0; i < k; ++i)
		printf("%s", ptr1[i]);

	delete_array(ptr1, k);
	return 0;
}