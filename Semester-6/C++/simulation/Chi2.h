#pragma once
#include "BinSampleGenerator.h"
#include "PROBDIST.H"
#include <iostream>
#include <cassert>

/**
* Пара из значения и ожидаемого числа его повторений в выборке
*/
struct theor_freq {
	double value = 0, freq = -1;
};

/**
* Класс предназначен для вычисления статистики критерия хи-квадрат и p-value.
* \example<main.cpp>
*/
class Chi2 {
private:
	/**
	* Эмперические частоты
	*/
	emp_freq* emperical = nullptr;
	/**
	* Теоретические частоты
	*/
	theor_freq* theoretical = nullptr;
	/**
	* Эмперические частоты после объединения интервалов
	*/
	int* emp_merged_freq = nullptr;
	/**
	* Теоретичесие частоты после объединения интервалов
	*/
	double* theor_merged_freq = nullptr;
	/**
	* Число состояний до объединения интервалов
	*/
	size_t k_ = 0;
	/**
	*Число степеней свободы
	*/
	int dof_ = -1; 
	double pvalue_ = -1;
	/**
	* Статистика критерия хи-квадрат
	*/
	double stat_ = -1;
	/**
	* Функция, выполняющая объединение интервалов, чтобы соблюдались условия применимости критерия хи-квадрат.
	*/
	void mergeIntervals();
public:
	/**
	* \brief Создает объект класса Chi2 на основе выборки и распределения
	*/
	Chi2(const BinSampleGenerator& sample, const Distribution& distr);
	/**
	* Конструктор по умолчанию
	*/
	Chi2() {}
	/**
	* Конструктор перемещения
	*/
	Chi2(Chi2&& other);
	/**
	* Конструктор копирования
	*/
	Chi2(const Chi2& other);
	/**
	* Эта функция позволяет задавать новые данные для критерия
	*/ 
	void SetData(const BinSampleGenerator& sample, const Distribution& distr);
	/**
	* \brief Возвращает число степеней свободы
	* \details Если dof_ == -1, то вызывает merge_intervals(), после чего возвращает значение dof_. Иначе --- сразу возвращает dof_.
	*/
	int dof();
	/**
	* \brief Возвращает значение pvalue_
	* \details Если pvalue_ уже вычислено, т.е. неотрицательно, то возвращает его, иначе --- сначала вычисляет.
	*/
	double pvalue();
	/**
	* \brief Возвращает stat_
	* \details Если stat_ уже вычислена, то есть неотрицательна, то возвращает значение stat_, иначе --- сначала вычисляет.
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