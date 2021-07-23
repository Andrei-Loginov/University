#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdio>
#include "header.h"
#include <time.h>
#include <Windows.h>

double PCFreq = 0.0;
__int64 CounterStart = 0;
const size_t length = 500;

void StartCounter();
double GetCounter();


int main(){
    char* str = new char[length];
    fgets(str, length,stdin);

    char* str_copy1 = new char[strlen(str) + 1], * str_copy2 = new char[strlen(str) + 1];
    str_copy1[strlen(str)] = '\0'; str_copy2[strlen(str)] = '\0';
    strcpy(str_copy1, str); 
    strcpy(str_copy2, str);

    int dots, commas, dots_cstring, commas_cstring;
    
    StartCounter();
    modify(str_copy1, dots, commas);
    std::cout << "Some time meassure:" << GetCounter() << "\n";
    printf("%d dots\n%d commas\n%s\n", dots, commas, str_copy1);

    StartCounter();
    modify_str(str_copy2, dots_cstring, commas_cstring);
    std::cout << "Some time measure: " << GetCounter() << "\n";
    printf("%d dots\n%d commas\n%s\n", dots_cstring, commas_cstring, str_copy1);
    system("pause");
    return 0;
}



void StartCounter(){
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        std::cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart) / 1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter(){
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}