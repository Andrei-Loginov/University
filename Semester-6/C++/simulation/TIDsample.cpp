#include "TIDsample.h"

TIDsample::TIDsample(const Distribution& distr) : BinSampleGenerator(distr) {
	prob_cumsum = new double[distr.size()];
	prob_cumsum[0] = distr[0].prob;
	for (int i = 1; i < distr.size(); prob_cumsum[i] = prob_cumsum[i - 1] + distr[i].prob, ++i);
}

TIDsample::TIDsample(const TIDsample& other) : BinSampleGenerator(other) {
	prob_cumsum = new double[distr.size()];
	for (int i = 0; i < distr.size(); ++i)
		prob_cumsum[i] = other.prob_cumsum[i];
}

TIDsample::TIDsample(TIDsample&& other) noexcept : BinSampleGenerator(std::move(other)) {
	prob_cumsum = other.prob_cumsum;
	other.prob_cumsum = nullptr;
}

void TIDsample::swap(TIDsample& other) noexcept {
	BinSampleGenerator::swap(other);
	std::swap(prob_cumsum, other.prob_cumsum);
}

TIDsample& TIDsample::operator=(TIDsample other) {
	this->swap(other);
	return *this;
}

size_t TIDsample::count_index(){
	double alpha = get_unif_real_01();
	int i = 0, j = distr.size() - 1, k;
	while (i < j) {
		k = (i + j) / 2;
		if (alpha <= prob_cumsum[k]) j = k;
		else i = k + 1;
	}
	return i;
}

TIDsample::~TIDsample() {
	if (prob_cumsum) delete[]prob_cumsum;
	//BinSampleGenerator::~BinSampleGenerator();
}