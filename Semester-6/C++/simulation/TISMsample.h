#pragma once
#include "BinSampleGenerator.h"

/**
* ���� ����� ������������ ��� ��������� ������� ������� �������� ������� � ��������������� ������������. 
*/

class TISMsample : public BinSampleGenerator{
protected:
	/*
	* ������������ ���������� ������ ��������� � distr, ������� ����� ����������� ��� ��������� ��������� ������� �� distr
	*/
	size_t count_index() override;
public:
	/**
	* ������� ������ TISMsample � �������� �������������� 
	*/
	TISMsample(const Distribution& distribution);
	/**
	* ����������� �����������
	*/
	TISMsample(const TISMsample& other);
	/**
	* ����������� �����������
	*/
	TISMsample(TISMsample&& other) noexcept;
	/**
	* ������������ ����� ������ this � other
	*/
	void swap(TISMsample& other);
	/**
	*  �������� ������������
	*/
	TISMsample& operator=(TISMsample& other);
};

