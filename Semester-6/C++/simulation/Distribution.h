#pragma once
#include <algorithm>

#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW


/**
Пара значение-вероятность 
*/
struct point {
	double value = 0, prob = 0;
	point(double val, double pr) : value(val), prob(pr) {};
	point() {}
};

/**
* Данный класс содержит в себе информацию о распределении в виде пар значение-вероятность.
*/

class Distribution{
	point* values = nullptr; 
	size_t size_ = 0;
public:
	Distribution() {}
	/**
	* Создает объект Distribution на основе массивов значений и вероятностей с k состояний. 
	*/
	Distribution(double* values, double* probs, size_t k);
	/** 
	Конструктор копирования
	*/
	Distribution(const Distribution& distr);
	/* *
	Конструктор перемещения
	*/
	Distribution(Distribution&& distr) noexcept;
	~Distribution();
	/**
	 Оператор присваивания
	 */
	Distribution& operator=(Distribution distr) noexcept;
	void swap(Distribution& other) noexcept;
	/**
	* Возвращает i-е состояние из распределения. 
	* \warning Не отслеживает корректность k.
	*/
	point& operator[](size_t i) const;
	/** 
	Сортировка состояний по вероятности, применяется в TISMsample
	*/
	void sort();
	size_t size() const { return size_; }
};

