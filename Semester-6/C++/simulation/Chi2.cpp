#include "Chi2.h"
//#define DEBUG_CHI2

Chi2::Chi2(const BinSampleGenerator& sample, const Distribution& distr) : emperical (new emp_freq[distr.size()]), 
																		theoretical(new theor_freq[distr.size()]), k_(distr.size()) {
	for (int i = 0; i < k_; ++i) {
		emperical[i] = sample.point(i);
		theoretical[i] = { distr[i].value, distr[i].prob * sample.size() };
	}
	std::sort(emperical, emperical + k_, [](const emp_freq& lhs, const emp_freq& rhs) {
		return lhs.value < rhs.value;
		});
	std::sort(theoretical, theoretical + k_, [](const theor_freq& lhs, const theor_freq& rhs) {
		return lhs.value < rhs.value;
		});
}

Chi2::Chi2(Chi2&& other) : emperical(other.emperical), theoretical(other.theoretical), emp_merged_freq(other.emp_merged_freq),
						theor_merged_freq(other.theor_merged_freq), k_(other.k_), dof_(other.dof_), pvalue_(other.pvalue_),
						stat_(other.stat_) {
	other.emperical = nullptr;
	other.theoretical = nullptr;
	other.emp_merged_freq = nullptr;
	other.theor_merged_freq = nullptr;
}

Chi2::Chi2(const Chi2& other) : k_(other.k_), dof_(other.dof_), pvalue_(other.pvalue_), stat_(other.stat_) {
	if (k_ > 0) {
		emperical = new emp_freq[k_];
		theoretical = new theor_freq[k_];
		for (size_t i = 0; i < k_; ++i) {
			theoretical[i] = other.theoretical[i];
			emperical[i] = other.emperical[i];
		}
		if (dof_ > 0) {
			emp_merged_freq = new int[dof_ + 1];
			theor_merged_freq = new double[dof_ + 1];
			for (size_t i = 0; i <= dof_; ++i) {
				emp_merged_freq[i] = other.emp_merged_freq[i];
				theor_merged_freq[i] = other.theor_merged_freq[i];
			}
		}
	}
}

void Chi2::SetData(const BinSampleGenerator& sample, const Distribution& distr) {
	delete[] emperical; emperical = nullptr; 
	delete[] theoretical; theoretical = nullptr; 
	delete[] theor_merged_freq; theor_merged_freq = nullptr; 
	delete[] emp_merged_freq; emp_merged_freq = nullptr; 

	dof_ = pvalue_ = stat_ = -1;
	k_ = distr.size();
	emperical = new emp_freq[k_];
	theoretical = new theor_freq[k_];
	for (int i = 0; i < k_; ++i) {
		emperical[i] = sample.point(i);
		theoretical[i] = { distr[i].value, distr[i].prob * sample.size() };
	}
	std::sort(emperical, emperical + k_, [](const emp_freq& lhs, const emp_freq& rhs) {
		return lhs.value < rhs.value;
		});
	std::sort(theoretical, theoretical + k_, [](const theor_freq& lhs, const theor_freq& rhs) {
		return lhs.value < rhs.value;
		});
}

void Chi2::mergeIntervals() {
	if (dof_ == -1) {
		emp_merged_freq = new int[k_];
		theor_merged_freq = new double[k_];
		dof_ = 0;
		for (int i = 0; i < k_; ++i, ++dof_) {
			for (emp_merged_freq[dof_] = 0, theor_merged_freq[dof_] = 0; i < k_ && theor_merged_freq[dof_] < 5; ++i) {
				emp_merged_freq[dof_] += emperical[i].freq;
				theor_merged_freq[dof_] += theoretical[i].freq;
			}
			if (theor_merged_freq[dof_] < 5) {
				emp_merged_freq[dof_ - 1] += emp_merged_freq[dof_];
				theor_merged_freq[dof_ - 1] += theor_merged_freq[dof_];
				--dof_;
			}
			--i;
		}
	}
	--dof_;
#ifdef DEBUG_CHI2
	for (int i = 0; i <= dof_; ++i)
		std::cout << emp_merged_freq[i] << " ";
	std::cout << "\n";
#endif
}

int Chi2::dof() {
	if (dof_ == -1) 
		mergeIntervals();
	return dof_;
}

double Chi2::CalcChi() {
	if (stat_ < 0) {
		if (dof_ == -1)
			mergeIntervals();
		stat_ = 0;
		for (size_t i = 0; i <= dof_; ++i)
			stat_ += pow(emp_merged_freq[i] - theor_merged_freq[i], 2) / theor_merged_freq[i];
	}
	return stat_;
}

double Chi2::pvalue() {
	if (pvalue_ < 0) {
		if (stat_ < 0)
			CalcChi();
		assert(dof_ > 0);
		pvalue_ = 1 - pChi(stat_, dof_);
	}
	return pvalue_;
}

Chi2::~Chi2() {
	delete[]theoretical; theoretical = nullptr; 
	delete[]emperical; emperical = nullptr; 
	delete[]emp_merged_freq; emp_merged_freq = nullptr;
	delete[]theor_merged_freq; theor_merged_freq = nullptr;
}