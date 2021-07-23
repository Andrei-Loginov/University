#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]){
	char input_name[50], output_name[50];
	if (argc <= 2) {
		if (argc < 2) {
			printf("You should run this program with 2 arguments: input file name and output file name\n");
			exit(0);
		}
		printf("You have not given output file name. Specify it: ");
		fgets(output_name, 50, stdin);
		output_name[strlen(output_name) - 1] = '\0';
	}
	else
		strcpy(output_name, argv[2]);
	strcpy(input_name, argv[1]);

	if (!file_exists(input_name)) {
		printf("Input file does not exists.\n");
		exit(0);
	}
	FILE* input = fopen(input_name, "r");
	if (!input) {
		printf("Can't open the input file.\n");
		exit(0);
	}
	
	char* str = new char[200];
	fgets(str, 200, input);
	fclose(input);

	int dots, commas;
	modify(str, dots, commas);

	int c = 'n';
	while (file_exists(output_name) && !(c == 'y' || c == 'Y')) {
		printf("Output file already exists. Rewrite it?\ny/n\n");
		c = getc(stdin);
		getc(stdin);
		if (c != 'y' && c != 'Y') {
			printf("Enter new input file name: ");
			fgets(output_name, 50, stdin);
			output_name[strlen(output_name) - 1] = '\0';
		}
	}

	FILE* output = fopen(output_name, "w");
	if (!output) {
		std::cout << "err\n";
		exit(0);
	}
	fprintf(output, "Dots: %d\nCommas: %d\n%s\n", dots, commas, str);
	fclose(output);
	return 0;
}