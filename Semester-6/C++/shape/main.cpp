#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

class shape {
protected: 
	int num;
public:
	int number() { return num; }
	virtual const char* name() = 0;
	virtual double area() = 0;
	void print() {
		std::cout << name() << " number " << number() << ". Area = " << area() << "\n";
	}
	virtual ~shape() {}
};

class circle : public shape {
protected:
	static int N;
	double center, radius;
public:
	circle(double cent, double rad) : center(cent), radius(rad) {
		num = ++circle::N;
	}
	const char* name() { return "circle"; }
	double area() override { return M_PI * radius * radius; }
};

int circle::N = 0;

class rectangle :public shape {
protected:
	static int N;
	double x1_, x2_, y1_, y2_;
public:
	rectangle(double x1, double y1, double x2, double y2): x1_(x1), x2_(x2), y1_(y1), y2_(y2) {
		num = ++rectangle::N;
	}
	const char* name() override { return "Circle"; }
	double area() override { return fabs((x1_ - x2_) * (y1_ - y2_)); }
};

int rectangle::N = 0;

void Sort(shape** arr, size_t size, bool(*cmp)(shape*, shape*)) {
	for (int i = size - 1; i > 0; --i) {
		for (int j = 0; j < i; ++j)
			if (!cmp(arr[j], arr[j+1]))
				std::swap(*(arr + j), *(arr + j + 1));
	}
}

bool area_cmp(shape* lhs, shape* rhs) {
	return (lhs->area() < rhs->area());
}

bool num_cmp(shape* lhs, shape* rhs) {
	return (lhs->number() < rhs->number());
}


int main() {
	circle S(0, 1);
	S.print();
	circle S1(0, 2);
	S1.print();
	rectangle r(-5, -5, 3, 2);
	r.print();
	rectangle r1(-1, -2, 5, 7);
	r1.print();

	shape** arr = new shape* [4];
	arr[0] = new circle(0, 1);
	arr[1] = new rectangle(-5, -5, 3, 2);
	arr[2] = new rectangle(-1, -2, 5, 7);
	arr[3] = new circle(0, 2);
	Sort(arr, 4, area_cmp);
	std::cout << "Sort by area:\n";
	for (int i = 0; i < 4; ++i)
		arr[i]->print();

	Sort(arr, 4, num_cmp);
	std::cout << "Sort by num:\n";
	for (int i = 0; i < 4; ++i)
		arr[i]->print();
	
	for (int i = 0; i < 4; ++i)
		delete arr[i];
	delete[] arr;
	return 0;
}