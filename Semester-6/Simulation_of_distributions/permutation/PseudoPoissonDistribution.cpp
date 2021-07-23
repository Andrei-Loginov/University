//
// Created by andrei on 08.06.2021.
//

#include "PseudoPoissonDistribution.h"
#include <iostream>

PseudoPoissonDistribution::PseudoPoissonDistribution(double lambda, int maxValue) : lambda_(lambda), maxValue_(maxValue){
    size_ = maxValue_ + 1;
    values = new Point[size_];
    double sum = 0;
    for (int i = 0; i < size_ - 1; ++i){
        values[i].value = i;
        values[i].prob = pow(lambda_, i) * exp(-lambda_);
        for (int j = 1; j <= i; ++j)
            values[i].prob /= j;
        sum += values[i].prob;
    }
    values[size_ - 1].value = size_ - 1;
    values[size_ - 1].prob = (1. - sum);
}