#include "header.h"

const unsigned char day_mask = 31;
const unsigned char month_mask = 15;
const unsigned short year_mask = 2047;

inline bool is_equal_sign(double left, double right) {
	return ((left > 0) == (right > 0));
}

void read_user(FILE* input, USER& item) {
	fscanf(input, "%lf", &(item.time));
	fseek(input, 1, SEEK_CUR);
	fscanf(input, "%s", item.browser);
	//fgets(item.address, ADRLEN, input);
	fscanf(input, "%s", item.address);
}

void read_date(FILE* input, DATE& item) {
	char str[11];
	fscanf(input, "%s", str);

	char* tok;
	tok = strtok(str, ".");
	item.day = atoi(tok);
	tok = strtok(NULL, ".");
	item.month = atoi(tok);
	tok = strtok(NULL, ".\0");
	item.year = atoi(tok);
}

void read_day(FILE* input, DAY& item) {
	read_date(input, item.date);
	fscanf(input, "%d", &item.users_num);
	item.users_num = std::min(item.users_num, USERSNUM);
	for (int i = 0; i < item.users_num; ++i)
		read_user(input, item.users[i]);
	qsort(item.users, item.users_num, sizeof(USER), (int(*) (const void*, const void*))comp_user_address);
}

int read_days(const char* fname, DAY* days) {
	FILE* input = fopen("input.txt", "r");
	size_t size;
	fscanf(input, "%d ", &size);
	size = std::min(size, NDAYS);

	for (size_t i = 0; i < size; ++i)
		read_day(input, days[i]);
	fclose(input);
	qsort(days, size, sizeof(DAY), (int(*) (const void*, const void*))comp_days_date);
	return size;
}

int read_days(FILE* input, DAY* days) {
	size_t size;
	fscanf(input, "%d", &size);
	size = std::min(size, NDAYS);
	for (size_t i = 0; i < size; ++i)
		read_day(input, days[i]);
	qsort(days, size, sizeof(DAY), (int(*) (const void*, const void*))comp_days_date);
	return size;
}

void print_user(const USER& item, FILE* output) {
	fprintf(output, "address: %s\nbrowser: %s\ntime: %lf\n", item.address, item.browser, item.time);
}

void print_date(const DATE& item, FILE* output ) {
	fprintf(output, "%d.%d.%d\n", item.day, item.month, item.year);
}

void print_day(const DAY& item, FILE* output) {
	print_date(item.date, output);
	fprintf(output, "%d\n", item.users_num);
	for (size_t i = 0; i < item.users_num; ++i)
		print_user(item.users[i], output);
}

int comp_date(const DATE* left, const DATE* right) {
	if (left->year != right->year) 
		return (left->year < right->year) ? -1 : 1;
	if (left->month != right->month) 
		return (left->month < right->month) ? -1 : 1;
	if (left->day != right->day) 
		return (left->day < right->day) ? -1 : 1;
	return 0;
}

int comp_days_date(const DAY* left, const DAY* right) {
	return comp_date(&(left->date), &(right->date));
}

int comp_user_browser(const USER* left, const USER* right) {
	return strcmp(left->browser, right->browser);
}

int comp_user_address(const USER* left, const USER* right) {
	return strcmp(left->address, right->address);
}

DAY* search(const DAY& item, DAY* ptr, size_t size, int(*cmp) (const DAY*, const DAY*)) {
	size_t left_x = 0, right_x = size - 1;
	int left_y = cmp(ptr, &item);
	if (!left_y) return ptr;
	if (left_y > 0) return nullptr;

	int right_y = cmp(ptr + right_x, &item);
	if (!right_y) return ptr + size - 1;
	if (right_y < 0) return nullptr;

	if (is_equal_sign(left_y, right_y)) return nullptr;

	while (left_x != right_x) {
		size_t mid = size / 2;
		int mid_y = cmp(ptr + mid, &item);
		if (!mid_y) return ptr + mid;
		if (mid_y > 0) right_x = mid - 1;
		else {
			left_x = mid + 1;
		}
	}
	
	return nullptr;
}

/*
bool operator<(const USER& left, const USER& right) {
	return (strcmp(left.address, right.address) < 0);
}

bool operator<(const DATE& left, const DATE& right) {
	if (left.year != right.year) return (left.year < right.year);
	if (left.month != right.month) return (left.month < right.month);
	return (left.day < right.day);
}

bool operator==(const DATE& left, const DATE& right) {
	return ((left.day == right.day) && (left.month == right.month) && (left.year == right.year));
}

bool operator<(const DAY& left, const DAY& right) {
	return (left.date < right.date);
}*/