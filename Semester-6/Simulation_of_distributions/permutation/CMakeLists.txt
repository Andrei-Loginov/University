cmake_minimum_required(VERSION 3.17)
project(permutation)

set(CMAKE_CXX_STANDARD 14)

add_executable(permutation main.cpp SingletonGenerator.cpp SingletonGenerator.h Permutation.cpp Permutation.h PROBDIST.H
        PROBDIST.CPP Distribution.h Distribution.cpp Chi2.h Chi2.cpp BinSampleGenerator.h BinSampleGenerator.cpp CyclesNumberSample.cpp CyclesNumberSample.h PseudoPoissonDistribution.cpp PseudoPoissonDistribution.h)