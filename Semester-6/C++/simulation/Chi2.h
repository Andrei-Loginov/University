#pragma once
#include "BinSampleGenerator.h"
#include "PROBDIST.H"
#include <iostream>
#include <cassert>

/**
* ���� �� �������� � ���������� ����� ��� ���������� � �������
*/
struct theor_freq {
	double value = 0, freq = -1;
};

/**
* ����� ������������ ��� ���������� ���������� �������� ��-������� � p-value.
* \example<main.cpp>
*/
class Chi2 {
private:
	/**
	* ������������ �������
	*/
	emp_freq* emperical = nullptr;
	/**
	* ������������� �������
	*/
	theor_freq* theoretical = nullptr;
	/**
	* ������������ ������� ����� ����������� ����������
	*/
	int* emp_merged_freq = nullptr;
	/**
	* ������������ ������� ����� ����������� ����������
	*/
	double* theor_merged_freq = nullptr;
	/**
	* ����� ��������� �� ����������� ����������
	*/
	size_t k_ = 0;
	/**
	*����� �������� �������
	*/
	int dof_ = -1; 
	double pvalue_ = -1;
	/**
	* ���������� �������� ��-�������
	*/
	double stat_ = -1;
	/**
	* �������, ����������� ����������� ����������, ����� ����������� ������� ������������ �������� ��-�������.
	*/
	void mergeIntervals();
public:
	/**
	* \brief ������� ������ ������ Chi2 �� ������ ������� � �������������
	*/
	Chi2(const BinSampleGenerator& sample, const Distribution& distr);
	/**
	* ����������� �� ���������
	*/
	Chi2() {}
	/**
	* ����������� �����������
	*/
	Chi2(Chi2&& other);
	/**
	* ����������� �����������
	*/
	Chi2(const Chi2& other);
	/**
	* ��� ������� ��������� �������� ����� ������ ��� ��������
	*/ 
	void SetData(const BinSampleGenerator& sample, const Distribution& distr);
	/**
	* \brief ���������� ����� �������� �������
	* \details ���� dof_ == -1, �� �������� merge_intervals(), ����� ���� ���������� �������� dof_. ����� --- ����� ���������� dof_.
	*/
	int dof();
	/**
	* \brief ���������� �������� pvalue_
	* \details ���� pvalue_ ��� ���������, �.�. ��������������, �� ���������� ���, ����� --- ������� ���������.
	*/
	double pvalue();
	/**
	* \brief ���������� stat_
	* \details ���� stat_ ��� ���������, �� ���� ��������������, �� ���������� �������� stat_, ����� --- ������� ���������.
	* \example <main.cpp>
	*/
	double CalcChi();
	~Chi2();
};

/**
* \code
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
* \endcode
*/