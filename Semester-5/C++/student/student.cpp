#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

const unsigned int NMARK = 5;
const unsigned int NSIMB = 10;
const unsigned int NSTUDENT = 100;

struct STUDENT {
    float avr = -1.0;
    char name[NSIMB];
    unsigned int mark[NMARK];
};

int input_all(STUDENT* ptr);
void compute_avr(STUDENT* ptr, int size);
int compare_avr(const STUDENT& left, const STUDENT& right);

int input_all(STUDENT* ptr) {
    size_t size;
    scanf("%d\n", &size);
    size = std::min(size, NSTUDENT);
    for (int i = 0; i < size; ++i) {
        gets_s(ptr[i].name, NSIMB);
        for (int j = 0; j < NMARK; ++j)
            scanf("%d", ptr[i].mark + j);
        fseek(stdin, 1, SEEK_CUR);
    }
    compute_avr(ptr, size);
    return size;
}

void compute_avr(STUDENT* ptr, int size) {
    for (int i = 0; i < size; ++i) {
        ptr[i].avr = 0.0;
        for (int j = 0; j < NMARK; ++j)
            ptr[i].avr += ptr[i].mark[j];
        ptr[i].avr /= NMARK;
    }
}

int compare_avr(const STUDENT &left, const STUDENT &right) {
    return (left.avr - right.avr);
}

void sort(STUDENT* arr, size_t size, int (*compare)(const STUDENT &left, const STUDENT& right)) {
    for (int i = size - 1; i > 0; --i)
        for (int j = 0; j < i; ++j)
            if (compare(arr[j], arr[j+1]) > 0) {
                std::swap(arr[j], arr[j + 1]);
            }
}

void to_file(const char* fname, STUDENT* ptr, int size) {
    FILE* output = fopen(fname, "wb");
    fwrite(ptr, sizeof(STUDENT), size, output);
    fclose(output);
}

void from_file(const char* fname, STUDENT* ptr, int& size) {
    FILE* input = fopen(fname, "rb");
    size_t begin = ftell(input);
    fseek(input, 0, SEEK_END);
    size_t end = ftell(input);
    size = std::min((end - begin) / sizeof(STUDENT), NSTUDENT);

    fseek(input, 0, SEEK_SET);

    fread(ptr, sizeof(STUDENT), size, input);
    compute_avr(ptr, size);

    fclose(input);
}

STUDENT* search(const STUDENT& item, STUDENT* ptr, int size, int(*compare)(const STUDENT& left, const STUDENT& right)) {
    for (int i = 0; i < size; ++i) {
        if (!compare(item, ptr[i]))
            return (ptr + i);
    }
    return nullptr;
}

void print_one(const STUDENT& item) {
    std::cout << item.name << " ";
    for (int i = 0; i < NMARK; std::cout << item.mark[i] << " ", ++i);
    std::cout << item.avr;
}

void print_all(const STUDENT* arr, int size) {
    for (int i = 0; i < size; ++i) {
        print_one(arr[i]);
        std::cout << "\n";
    }
}

int cmp_name(const STUDENT& left, const STUDENT& right) {
    return strcmp(left.name, right.name);
}


int main(){
    STUDENT arr[NSTUDENT];
    int size = input_all(arr);

    print_all(arr, size);
    to_file("output.txt", arr, size);
    
    from_file("output.txt", arr, size);
    std::cout << "From file:\n";
    print_all(arr, size);
    sort(arr, size, cmp_name);
    std::cout << "Sorted:\n";
    print_all(arr, size);
    STUDENT somebody = arr[1];

    from_file("output.txt", arr, size);
    STUDENT* ptr;
    if ((ptr = search(somebody, arr, size, cmp_name)) == nullptr) {
        std::cout << "not found\n";
    }
    else {
        std::cout << "Found:\n";
        print_one(*ptr);
        std::cout << "\n";
    }

    system("pause");
    return 0;
}

