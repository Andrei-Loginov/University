//
// Created by andrei on 08.06.2021.
//

#include "CyclesNumberSample.h"
#include <iostream>

CyclesNumberSample::CyclesNumberSample(int n, int k): permutation(n), cycleLen(k), permLen(n){
    assert(n > 0 && k > 0 && k < n);
    int dSize = n / k + 1;
    double* vals = new double[dSize];
    double* probs = new double[dSize];
    for (int i = 0; i < n / k + 1; ++i){
        vals[i] = i;
        probs[i] = double(1) / dSize;
    }
    distr = Distribution(vals, probs, dSize);
    delete[]vals;
    delete[]probs;
    grouped_sample = new emp_freq[dSize];
    for (int i = 0; i < dSize; ++i)
        grouped_sample[i] = {distr[i].value, 0};
}

size_t CyclesNumberSample::count_index() {
    std::vector<int> p = permutation();
    int count = 0;
    std::vector<bool> used(distr.size(), false);
    for (int i = 0; i < p.size(); ++i){
        int len = 0;
        if (!used[i]){
            used[i] = true;
            ++len;
            int curr = i;
            while (p[curr] != i){
                ++len;
                curr = p[curr];
                used[curr] = true;
            }
        }
        if (len == cycleLen) ++count;
    }
    return count;
}

int CyclesNumberSample::getMax() const {
    return permLen / cycleLen;
}