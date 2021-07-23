#pragma once
#include "BinSampleGenerator.h"

/**
* Этот класс предназначен для генерации выборки методом обратных функций с упорядочиванием вероятностей. 
*/

class TISMsample : public BinSampleGenerator{
protected:
	/*
	* Осуществляет вычисление номера состояние в distr, который будет использован для получения случайной велчины из distr
	*/
	size_t count_index() override;
public:
	/**
	* Создает объект TISMsample с заданным распределением 
	*/
	TISMsample(const Distribution& distribution);
	/**
	* Конструктор копирования
	*/
	TISMsample(const TISMsample& other);
	/**
	* Конструктор перемещения
	*/
	TISMsample(TISMsample&& other) noexcept;
	/**
	* Осуществляет обмен данных this и other
	*/
	void swap(TISMsample& other);
	/**
	*  Оператор присваивания
	*/
	TISMsample& operator=(TISMsample& other);
};

