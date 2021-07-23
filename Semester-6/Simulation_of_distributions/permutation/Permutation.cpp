//
// Created by andrei on 07.06.2021.
//

#include "Permutation.h"

Permutation::Permutation(size_t size) : size_(size), moves(std::vector<int>(size)){
    for (int i = 0; i < size_; ++i)
        moves[i] = i;
}

size_t Permutation::size() {
    return size_;
}

std::vector<int> Permutation::operator()() {
    for (int i = size_ - 1; i > 0; --i){
        unif = std::uniform_int_distribution<int>(0, i);
        std::swap(moves[i], moves[unif(SingletonGenerator::get_mt())]);
    }
    return moves;
}