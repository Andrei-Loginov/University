//
// Created by andrei on 08.06.2021.
//
#define _USE_MATH_DEFINES
#ifndef PERMUTATION_PSEUDOPOISSONDISTRIBUTION_H
#define PERMUTATION_PSEUDOPOISSONDISTRIBUTION_H
#include "Distribution.h"
#include <cmath>



class PseudoPoissonDistribution : public Distribution {
public:
    PseudoPoissonDistribution(double lambda, int maxValue);
protected:
    double lambda_;
    int maxValue_;
};


#endif //PERMUTATION_PSEUDOPOISSONDISTRIBUTION_H
