#include "TISMsample.h"

TISMsample::TISMsample(const Distribution& distribution) : BinSampleGenerator(distribution) {
}



TISMsample::TISMsample(const TISMsample& other) : BinSampleGenerator(other) { 
}

size_t TISMsample::count_index(){
	double alpha = get_unif_real_01();
	int i;
	double sum = distr[0].prob;
	for (i = 0; i < distr.size() && sum < alpha; sum += distr[++i].prob);
	return i;
}

TISMsample::TISMsample(TISMsample&& other) noexcept : BinSampleGenerator(std::move(other)){
}

void TISMsample::swap(TISMsample& other) {
	BinSampleGenerator::swap(other);
}

TISMsample& TISMsample::operator=(TISMsample& other) {
	this->swap(other);
	return *this;
}