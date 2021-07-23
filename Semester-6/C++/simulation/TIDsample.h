#pragma once
#include "BinSampleGenerator.h"

class TIDsample : public BinSampleGenerator{
protected:
	/**
	* ����������� ����� ������������. ������������ ��� ���������� ������ ���������
	*/
	double* prob_cumsum;
	/**
	* ���������� ������ ��������� � ������� ������ ��������� 
	*/
	size_t count_index() override;
public:
	/**
	* ����������� � �������� ��������������
	*/
	TIDsample(const Distribution& distr);
	/**
	* ����������� �����������
	*/
	TIDsample(const TIDsample& other);
	/**
	* ����������� �����������
	*/
	TIDsample(TIDsample&& other) noexcept;
	/**
	* ������������ ����� ������� ����� this � other
	*/
	void swap(TIDsample& other) noexcept;
	/**
	* �������� ������������
	*/
	TIDsample& operator=(TIDsample other);
	~TIDsample();
};

