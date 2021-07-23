#pragma once
#include "SingletonGenerator.h"
#include "Distribution.h"

/**
* ��� ��������� ������������ ��� �������� �������� ��������������� �������.
**/
struct emp_freq{
	/// ��������
	double value = 0.; 
	///����� ���������� �������� � �������
	unsigned int freq = 0;
};

/**
* ����������� ����� ���������� �������. 
**/

class BinSampleGenerator{
protected:
	size_t size_ = 0;
	double* sample = nullptr;
	/// ������� � ��������������� ����.
	emp_freq* grouped_sample = nullptr; 
	std::uniform_real_distribution<double> unif_real_01; 
	Distribution distr;
/**
* \brief ���������� ��������� ����� �� ������������ �� ������� [0, 1] �������������
* \details � �������� ���� ������������ std::mt_19937, ������������������ � ������ SingletonGenerator, ����� ���� unif_real_01 
* �������� ����� �� U[0,1]
**/
	double get_unif_real_01();
/**
* ����������� �������, ���������� �� ����� ������ ������ ��������� � distr. 
**/
	virtual size_t count_index() = 0;
public:
	/**
	����������� �� ���������, ���������� ������ unif_real_01
	*/
	BinSampleGenerator();
	/**
	* ������������ ������ BinSampleGenerator � �������� ��������������
	*/
	BinSampleGenerator(const Distribution& distribution);
	/**
	* ����������� �����������
	*/
	BinSampleGenerator(const BinSampleGenerator& other) noexcept;
	/**
	* ����������� �����������
	*/
	BinSampleGenerator(BinSampleGenerator&& other) noexcept;
	void swap(BinSampleGenerator& other);
	size_t size() const { return size_; }
	/**
	*  ��� ������ ���� ������� ������������ ������� �� ������������� distr ������ size_. � ����������������� ���� ��� �������� � sample, 
	* � ��������������� --- � grouped_sample
	**/
	void Simulate(size_t k);
	/**
	* ��������� �������� ������ � k-��� �������� �������. 
	\warning ������ ������� �� �����������, ����� �� k ����� 0 � size_. 
	**/
	double& operator[](size_t i);
	/**
	* \brief ���������� ��������� �������� �� ������������� distr.
	* \details � ������� count_index() �������� ����� ��������� � ���������� distr[i].value
	**/
	double get_one();
	Distribution get_distr() const { return distr; }
	/**
	* ���������� i-� ��������� �� ������� � ��������������� ����
	* \warning ������� �� ����������� ������������ ��������� k.
	**/
	emp_freq point(size_t i) const { return grouped_sample[i]; }
	virtual ~BinSampleGenerator();
};

