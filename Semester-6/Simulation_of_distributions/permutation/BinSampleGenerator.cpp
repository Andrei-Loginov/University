
#include "BinSampleGenerator.h"


BinSampleGenerator::BinSampleGenerator() {
	unif_real_01 = std::uniform_real_distribution<double>(0.0, 1.0);
}

BinSampleGenerator::BinSampleGenerator(const Distribution& distribution) : distr(distribution) {
	unif_real_01 = std::uniform_real_distribution<double>(0.0, 1.0);
	grouped_sample = new emp_freq[distr.size()];
	for (int i = 0; i < distr.size(); ++i) {
		grouped_sample[i] = { distr[i].value, 0 };
	}
}

BinSampleGenerator::BinSampleGenerator(const BinSampleGenerator& other) noexcept : size_(other.size_), sample(new double[other.size_]),
grouped_sample(new emp_freq[other.distr.size()]), distr(other.distr), unif_real_01(other.unif_real_01) {
	for (size_t i = 0; i < size_; ++i) {
		sample[i] = other.sample[i];
	}
	for (size_t i = 0; i < distr.size(); ++i)
		grouped_sample[i] = other.grouped_sample[i];
}

BinSampleGenerator::BinSampleGenerator(BinSampleGenerator&& other) noexcept : size_(other.size_), sample(other.sample),
grouped_sample(other.grouped_sample), distr(std::move(other.distr)), unif_real_01(std::move(other.unif_real_01)) {
	other.size_ = 0;
	other.sample = nullptr;
	other.grouped_sample = nullptr;
}

double BinSampleGenerator::get_unif_real_01() {
	return unif_real_01(SingletonGenerator::get_mt());
}

double& BinSampleGenerator::operator[](size_t i) {
	return sample[i];
}

double BinSampleGenerator::get_one() {
	return distr[count_index()].value;
}

void BinSampleGenerator::Simulate(size_t k) {
	if (size_ != 0) {
		delete[]sample;
		for (int i = 0; i < distr.size(); ++i)
			grouped_sample[i].freq = 0;
	}
	size_ = k;
	sample = new double[k];
	for (int i = 0; i < size_; ++i) {
		size_t ind = count_index();
		sample[i] = distr[ind].value;
		++grouped_sample[ind].freq;
	}
}

void BinSampleGenerator::swap(BinSampleGenerator& other) {
	std::swap(size_, other.size_);
	std::swap(sample, other.sample);
	std::swap(grouped_sample, other.grouped_sample);
	std::swap(unif_real_01, other.unif_real_01);
	distr.swap(other.distr);
}



BinSampleGenerator::~BinSampleGenerator() {
	delete[]sample;
	delete[]grouped_sample;
}

