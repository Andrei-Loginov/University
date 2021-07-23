#pragma once
#include "SingletonGenerator.h"
#include "Distribution.h"

/**
* Эта структура используется для хранения элемента сгруппированной выборки.
**/
struct emp_freq{
	/// Значение
	double value = 0.; 
	///Число повторений значения в выборке
	unsigned int freq = 0;
};

/**
* Асбтрактный класс генератора выборки. 
**/

class BinSampleGenerator{
protected:
	size_t size_ = 0;
	double* sample = nullptr;
	/// Выборка в сгруппированном виде.
	emp_freq* grouped_sample = nullptr; 
	std::uniform_real_distribution<double> unif_real_01; 
	Distribution distr;
/**
* \brief Возвращает случайное число из равномерного на отрезке [0, 1] распределения
* \details В качестве ГПСЧ используется std::mt_19937, инициализированный в классе SingletonGenerator, после чего unif_real_01 
* получаем число из U[0,1]
**/
	double get_unif_real_01();
/**
* Виртуальная функция, отвечающая за выбор номера номера состояния в distr. 
**/
	virtual size_t count_index() = 0;
public:
	/**
	Конструктор по умолчанию, определяет только unif_real_01
	*/
	BinSampleGenerator();
	/**
	* Конструирует объект BinSampleGenerator с заданным распределением
	*/
	BinSampleGenerator(const Distribution& distribution);
	/**
	* Конструктор копирования
	*/
	BinSampleGenerator(const BinSampleGenerator& other) noexcept;
	/**
	* Конструктор перемещения
	*/
	BinSampleGenerator(BinSampleGenerator&& other) noexcept;
	void swap(BinSampleGenerator& other);
	size_t size() const { return size_; }
	/**
	*  При вызове этой функции генерируется выборка из распределения distr объема size_. В несгруппированном виде она хранится в sample, 
	* в сгруппированном --- в grouped_sample
	**/
	void Simulate(size_t k);
	/**
	* Позволяет получить доступ к k-ому элементу выборки. 
	\warning Данная функция не отслеживает, лежит ли k между 0 и size_. 
	**/
	double& operator[](size_t i);
	/**
	* \brief Возвращает случайную величину из распределения distr.
	* \details С помощью count_index() выбирает номер состояния и возвращает distr[i].value
	**/
	double get_one();
	Distribution get_distr() const { return distr; }
	/**
	* Возвращает i-е состояние из выборки в сгруппированном виде
	* \warning Функция не отслеживает корректность параметра k.
	**/
	emp_freq point(size_t i) const { return grouped_sample[i]; }
	virtual ~BinSampleGenerator();
};

