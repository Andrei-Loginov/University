//
// Created by andrei on 08.06.2021.
//

#ifndef PERMUTATION_CYCLESNUMBERSAMPLE_H
#define PERMUTATION_CYCLESNUMBERSAMPLE_H
#include "BinSampleGenerator.h"
#include "Permutation.h"

class CyclesNumberSample : public BinSampleGenerator {
public:
    CyclesNumberSample(int n, int k);
    int getMax() const;
protected:
    size_t count_index() override;
    Permutation permutation;
    int cycleLen, permLen;
};


#endif //PERMUTATION_CYCLESNUMBERSAMPLE_H
