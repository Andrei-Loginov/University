//
// Created by andrei on 07.06.2021.
//

#include "SingletonGenerator.h"


std::mt19937 SingletonGenerator::mersennetwister;

std::mt19937& SingletonGenerator::get_mt() {
    return mersennetwister;
}