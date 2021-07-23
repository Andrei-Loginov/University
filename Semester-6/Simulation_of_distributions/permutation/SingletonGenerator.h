//
// Created by andrei on 07.06.2021.
//

#ifndef PERMUTATION_SINGLETONGENERATOR_H
#include <random>
#define PERMUTATION_SINGLETONGENERATOR_H


class SingletonGenerator {
    static std::mt19937 mersennetwister;
public:
    static std::mt19937& get_mt();
};


#endif //PERMUTATION_SINGLETONGENERATOR_H
