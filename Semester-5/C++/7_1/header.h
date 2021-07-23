#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <cstdlib>

const unsigned int ADRLEN = 50;
const unsigned int BROWSERLEN = 20;
const unsigned int USERSNUM = 100;
const unsigned int NDAYS = 50;

struct USER {
	double time;
	char browser[BROWSERLEN];
	char address[ADRLEN];
};

struct DATE {
	unsigned char day;
	unsigned char month;
	unsigned short year;
};

struct DAY {
	DATE date;
	size_t users_num;
	USER users[USERSNUM];
	DAY() {}
	DAY(const DATE& dat) : date(dat), users_num(0) {}
};



void read_user(FILE* input, USER& item);
void read_date(FILE* input, DATE& item);
void read_day(FILE* input, DAY& item);
int read_days(const char* fname, DAY* days); //memory for days must be allocated
int read_days(FILE* input, DAY* days); //memory for days must be allocated

void print_user(const USER& item, FILE* output = stdout);
void print_date(const DATE& item, FILE* output = stdout);
void print_day(const DAY& item, FILE* output = stdout);
//void print_day(const DAY& item, char* fname);

int comp_date(const DATE* left, const DATE* right);
int comp_days_date(const DAY* left, const DAY* right);
int comp_user_browser(const USER* left, const USER* right);
int comp_user_address(const USER* left, const USER* right);

DAY* search(const DAY& item, DAY* ptr, size_t size ,int(*cmp) (const DAY*, const DAY*));

/*
bool operator<(const USER& left, const USER& right);
bool operator<(const DATE& left, const DATE& right);
bool operator==(const DATE& left, const DATE& right);
bool operator<(const DAY& left, const DAY& right);
*/