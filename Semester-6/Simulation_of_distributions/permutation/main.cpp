#include <iostream>
#include "Permutation.h"
#include "CyclesNumberSample.h"
#include "PseudoPoissonDistribution.h"
#include "Chi2.h"

int main() {
    std::random_device rd;
    int seed = rd();
    //std::cout << seed << "\n";
    SingletonGenerator::get_mt().seed(seed);
    CyclesNumberSample num(100, 3);
    PseudoPoissonDistribution pois(1 / 3., num.getMax());
    num.Simulate(100000);
    Chi2 test(num, pois);
    std::cout << test.pvalue() << " ";
    return 0;
}
