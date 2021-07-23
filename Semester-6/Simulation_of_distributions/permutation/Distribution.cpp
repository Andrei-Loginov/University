
#include "Distribution.h"

Distribution::Distribution(double* val, double* prob, size_t k) : values(new Point[k]), size_(k) {
	for (size_t i = 0; i < size_; ++i)
		values[i] = Point(val[i], prob[i]);
}

Distribution::Distribution(const Distribution& distr) : values(new Point[distr.size_]) , size_(distr.size_) {
	
	for (size_t i = 0; i < size_; ++i)
		values[i] = distr.values[i];
}

Distribution::Distribution(Distribution&& distr) noexcept : values(distr.values), size_(distr.size_){
	distr.values = nullptr;
	distr.size_ = 0;
}

Distribution::~Distribution() {
	delete[] values;
}

Distribution& Distribution::operator=(Distribution distr) noexcept {
	this->swap(distr);
	return *this;
}

void Distribution::swap(Distribution& other) noexcept {
	std::swap(other.values, values);
	std::swap(other.size_, size_);
}

Point& Distribution::operator[](size_t i) const {
	return values[i];
}

void Distribution::sort() {
	std::sort(values, values + size_,
		[](const Point& lhs, const Point& rhs) {
			return (lhs.prob > rhs.prob);
		});
}

