#pragma once
#include <algorithm>
#include <cstring>
#define _CRT_SECURE_NO_WARNINGS

struct Point {
	double value = 0, prob = 0;
	Point(double val, double pr) : value(val), prob(pr) {};
	Point() {}
};

class Distribution {
protected:
	Point* values = nullptr;
	size_t size_ = 0;
public:
	Distribution() {}
	Distribution(double* values, double* probs, size_t k);
	Distribution(const Distribution& distr);
	Distribution(Distribution&& distr) noexcept;
	~Distribution();
	Distribution& operator=(Distribution distr) noexcept;
	void swap(Distribution& other) noexcept;
	Point& operator[](size_t i) const;
	void sort();
	size_t size() const { return size_; }
};

