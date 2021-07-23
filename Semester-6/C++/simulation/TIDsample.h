#pragma once
#include "BinSampleGenerator.h"

class TIDsample : public BinSampleGenerator{
protected:
	/**
	* Накопленные суммы вероятностей. Используются для вычисления номера состояния
	*/
	double* prob_cumsum;
	/**
	* Вычисление номера состояния с помощью метода дихотомии 
	*/
	size_t count_index() override;
public:
	/**
	* Конструктор с заданным распределением
	*/
	TIDsample(const Distribution& distr);
	/**
	* Конструктор копирования
	*/
	TIDsample(const TIDsample& other);
	/**
	* Конструктор перемещения
	*/
	TIDsample(TIDsample&& other) noexcept;
	/**
	* Осуществляет обмен данными между this и other
	*/
	void swap(TIDsample& other) noexcept;
	/**
	* Оператор присваивания
	*/
	TIDsample& operator=(TIDsample other);
	~TIDsample();
};

