//
// Created by andrei on 07.06.2021.
//

#ifndef PERMUTATION_PERMUTATION_H
#include "SingletonGenerator.h"
#include <vector>
#define PERMUTATION_PERMUTATION_H



class Permutation {
public:
    Permutation(size_t size);
    size_t size();
    std::vector<int> operator()();
private:
    size_t size_;
    std::vector<int> moves;
    std::uniform_int_distribution<int> unif;
};


#endif //PERMUTATION_PERMUTATION_H
