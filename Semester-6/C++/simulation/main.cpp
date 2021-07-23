#include <iostream>
#include "Distribution.h"
#include "TISMsample.h"
#include "TIDsample.h"
#include "Chi2.h"


int main(){
	std::random_device rd;
	SingletonGenerator::get_mt().seed(rd());

	double values[] = { 1, 2, 3, 4, 5 }, probs[] = { 0.3, 0.5, 0.05, 0.03, 0.12 };
	double alt_values[] = { 1, 2, 3, 4, 5 }, alt_probs[] = { 0.35, 0.45, 0.05, 0.03, 0.12 };
	int k = 5;
	Distribution d1(values, probs, k), d2(alt_values, alt_probs, k);
	TISMsample tism(d1);
	tism.Simulate(1000);
	std::cout << "TISM:\n";
	for (int i = 0; i < tism.get_distr().size(); ++i) {
		std::cout << tism.point(i).value << "\t" << tism.get_distr()[i].prob << "\t" << tism.point(i).freq << "\n";
	}
	Chi2 test(tism, d1);
	int* cdf = new int[20];
	for (int i = 0; i < 20; ++i)
		cdf[i] = 0;
	for (int i = 0; i < 1000; ++i) {
		tism.Simulate(1000);
		test.SetData(tism, d1);
		++cdf[int(test.pvalue() * 20)];
	}
	std::cout << "P-level CDF:\n";
	for (int i = 1; i < 20; ++i) {
		cdf[i] += cdf[i - 1];
	}
	for (int i = 0; i < 20; ++i)
		std::cout << cdf[i] << "\n";
	delete[]cdf;
	return 0;
}

