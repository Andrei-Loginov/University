#include <iostream>
#include <cassert>

template <typename Type>
class Array {
private:
    Type* a_;
    size_t n_ = 0;
public:
    explicit Array(size_t n, Type el = 0);
    explicit Array(Type el = 0);
    Array(const Array& arr);

    ~Array();

    Array& assign(const Array& arr);

    Type get(size_t index) const;
    size_t size() const { return n_; }
    bool set(size_t index, Type value);

    void print() const;
    friend std::ostream& operator<<(std::ostream& stream, const Array& arr) {
        for (size_t i = 0; i < arr.n_; stream << arr.a_[i] << " ", ++i);
        return stream;
    }
};

template <typename Type>
Array<Type>::Array(size_t n, Type el) :n_(n), a_(new Type[n]{el}) {
    std::cout << "Array(n, el)\n";
    for (size_t i = 0; i < n_; a_[i] = el, ++i);
}

template <typename Type>
Array<Type>::Array(Type el) : n_(1), a_(new Type[1]{ el }) {
    std::cout << "Array(el)\n";
}

template<typename Type>
Array<Type>::Array(const Array& arr) : n_(arr.size()), a_(new Type[arr.size()]) {
    std::cout << "Array(arr)\n";
    for (size_t i = 0; i < n_; ++i)
        a_[i] = arr.get(i);
}

template<typename Type>
Array<Type>::~Array() {
    std::cout << "~Array()\n";
    if (!n_)
        delete[]a_;
}

template<typename Type>
Array<Type>& Array<Type>::assign(const Array& arr) {
    if (this != &arr) {
        if (n_ != 0) delete[]a_;

        n_ = arr.size();
        a_ = new Type[n_];

        for (size_t i = 0; i < n_; ++i)
            a_[i] = arr.get(i);
    }
    return *this;
}

template<typename Type>
Type Array<Type>::get(size_t index) const {
    assert(index < n_);
    return a_[index];
}

template <typename Type>
bool Array<Type>::set(size_t index, Type value) {
    if (index > n_) return false;
    a_[index] = value;
    return true;
}


template<typename Type>
void Array<Type>::print() const {
    for (size_t i = 0; i < n_; std::cout << a_[i] << " ", ++i);
}

std::size_t operator""_sz(unsigned long long x) { return x; }

int main() {
    Array<double> arr1(4, 3.14);
    std::cout << "arr1: "; arr1.print(); std::cout << "\n";

    Array<int> arr2(5);
    std::cout << "arr2: " << arr2 << "\n";

    Array<int> arr3(3, 25);
    std::cout << "arr3: " << arr3 << "\n";

    std::cout << "arr2.assign(arr3): " << arr2.assign(arr3) << "\n";
    std::cout << "arr2: " << arr2 << "\n";

    arr3.set(2, 19);
    std::cout << "arr3.set(2, 19): " << arr3 << "\n";

    Array<double> arr4(5_sz);
    std::cout << "arr4 : " << arr4 << "\n";

    Array<double> arr5;
    std::cout << "arr5: " << arr5 << "\n";

    Array<double> arr6(arr1);
    std::cout << "arr6 : " << arr6 << "\n";

    std::cout << "arr6.get(1) " << arr6.get(1) << "\n";
    return 0;
}
