#include <iostream>
#include <fstream>
#include <cstring>

class complex {
private:
    double real = 0;
    double imaginary = 0;

public:
    complex() = default;
    complex(double Re, double Im) : real(Re), imaginary(Im) {};
    explicit complex(const char* Re) : real(atoi(Re)) {};
    complex(double Re) : real(Re) {};
    void set(double real = 0, double imaginary = 0) { this->real = real; this->imaginary = imaginary; }
    void set_real(double real) { this->real = real; }
    void set_imaginary(double imaginary)  { this->imaginary = imaginary; }

    double get_real() const { return real; }
    double get_imaginary() const { return imaginary; }


    friend complex sum(complex left, complex right) {
        return left.add(right);
    }
    complex& add(const complex &number) {
        this->real += number.real;
        this->imaginary += number.imaginary;
        return *this;
    }

    complex sum(complex right) const {
        return right.add(*this);
    }

    complex operator+=(const complex& right) {
        this->real += right.real;
        this->imaginary += right.imaginary;
        return *this;
    }


    friend complex operator+(complex left, complex right) {
        return right.add(left);
    }

    complex operator++() {
        ++(this->real);
        return *this;
    }

    complex operator++(int) {
        complex temp(*this);
        ++(this->real);
        return temp;
    }

};

std::ostream& operator<<(std::ostream& stream, const complex& number) {
    stream << number.get_real() << " + " << number.get_imaginary() << "*i";
    return stream;
}


int main(){
    complex a, b;
    a.set(12, 5);
    b.set(3, 6);
    std::cout << "a= " << a << "\n" << "b = " << b << "\n";
    a += b;
    std::cout << "a +=b;\t" << a << "\n";
    std::cout << "a+b;\t" << a + b << "\n";
    std::cout << "a++;\t" << a++ << "\na = " << a << "\n";
    std::cout << "++a;\t" << ++a << "\n";
    complex c = a + b;
    std::cout << "c = " << c << "\n";
    std::cout << a + b + c;
    return 0;
}

