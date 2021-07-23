#pragma once
#include "SingletonGenerator.h"
#include "Distribution.h"
#include <cassert>

struct emp_freq{
	double value = 0.;
	unsigned int freq = 0;
};

class BinSampleGenerator{
protected:
	size_t size_ = 0;
	double* sample = nullptr;
	emp_freq* grouped_sample = nullptr;
	std::uniform_real_distribution<double> unif_real_01;
	Distribution distr;
	double get_unif_real_01();
	virtual size_t count_index() = 0;
public:
	BinSampleGenerator();
	BinSampleGenerator(const Distribution& distribution);
	BinSampleGenerator(const BinSampleGenerator& other) noexcept;
	BinSampleGenerator(BinSampleGenerator&& other) noexcept;
	void swap(BinSampleGenerator& other);
	size_t size() const { return size_; }
	void Simulate(size_t k);
	double& operator[](size_t i);
	double get_one();
	Distribution get_distr() const { return distr; }
	emp_freq point(size_t i) const { return grouped_sample[i]; }
	virtual ~BinSampleGenerator();
};

