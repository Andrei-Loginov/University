#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>



int main() {
	char str[7], c;
	char curr_len = 0;
	while ((str[curr_len] = _getch()) != '\r' && curr_len < 6) {
		if (isdigit(str[curr_len]) || (curr_len == 0 && str[curr_len] == '-'))
			printf("%c", str[curr_len++]);
	}
	str[curr_len++] = '\0';
	short num = atoi(str);
	printf("\n%d", num);
	return 0;
}
