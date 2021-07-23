#pragma once
#include <algorithm>

#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW


/**
���� ��������-����������� 
*/
struct point {
	double value = 0, prob = 0;
	point(double val, double pr) : value(val), prob(pr) {};
	point() {}
};

/**
* ������ ����� �������� � ���� ���������� � ������������� � ���� ��� ��������-�����������.
*/

class Distribution{
	point* values = nullptr; 
	size_t size_ = 0;
public:
	Distribution() {}
	/**
	* ������� ������ Distribution �� ������ �������� �������� � ������������ � k ���������. 
	*/
	Distribution(double* values, double* probs, size_t k);
	/** 
	����������� �����������
	*/
	Distribution(const Distribution& distr);
	/* *
	����������� �����������
	*/
	Distribution(Distribution&& distr) noexcept;
	~Distribution();
	/**
	 �������� ������������
	 */
	Distribution& operator=(Distribution distr) noexcept;
	void swap(Distribution& other) noexcept;
	/**
	* ���������� i-� ��������� �� �������������. 
	* \warning �� ����������� ������������ k.
	*/
	point& operator[](size_t i) const;
	/** 
	���������� ��������� �� �����������, ����������� � TISMsample
	*/
	void sort();
	size_t size() const { return size_; }
};

