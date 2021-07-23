#pragma once
#include "BinSampleGenerator.h"
#include "PROBDIST.H"
#include <iostream>


struct theor_freq {
	double value = 0, freq = -1;
};

class Chi2 {
private:
	emp_freq* empirical = nullptr;
	theor_freq* theoretical = nullptr;
	int* emp_merged_freq = nullptr;
	double* theor_merged_freq = nullptr;
	size_t k_ = -1, dof_ = -1; 
	double pvalue_ = -1, stat_ = -1;
	void mergeIntervals();
	void swap(Chi2& other) { std::swap(*this, other); }
public:
	Chi2(const BinSampleGenerator& sample, const Distribution& distr);
	Chi2() {}
	Chi2(Chi2&& other);
	Chi2(const Chi2& other);
	void SetData(const BinSampleGenerator& sample, const Distribution& distr);
	size_t dof();
	double pvalue();
	double CalcChi();
	Chi2& operator=(Chi2 other) {
		this->swap(other);
		return *this;
	}
	~Chi2();
};

