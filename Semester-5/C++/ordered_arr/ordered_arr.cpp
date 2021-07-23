#include <iostream>
#include <cassert>
#include <algorithm>

template <typename Type>
class Array {
private:
    Type* a_;
    size_t n_ = 0;

    void sort() { std::sort(a_, a_ + n_); }
public:
    explicit Array(size_t n, Type el = 0);
    explicit Array(Type el = 0);
    explicit Array(const Array& left, const Array& right);
    Array(const Array& arr);

    ~Array();

    Array& assign(const Array& arr);

    Type get(size_t index) const;
    size_t size() const { return n_; }
    bool set(size_t index, Type value);

    friend Array merge(const Array& left, const Array& right) {
        Array<Type> ans(left.size() + right.size(), 0);
        size_t i, j, k;
        i = j = k = 0;

        while (i < left.size() && j < right.size())
            ans.a_[k++] = (left.get(i) < right.get(j)) ? left.get(i++) : right.get(j++);

        while (i < left.n_)
            ans.a_[k++] = left.get(i++);

        while (j < right.n_)
            ans.a_[k++] = right.get(j++);

        return ans;
    }

    void print() const;
    friend std::ostream& operator<<(std::ostream& stream, const Array& arr) {
        for (size_t i = 0; i < arr.n_; stream << arr.a_[i] << " ", ++i);
        return stream;
    }
};

template <typename Type>
Array<Type>::Array(size_t n, Type el) :n_(n), a_(new Type[n]{ el }) {
    //std::cout << "Array(n, el)\n";
    for (size_t i = 0; i < n_; a_[i] = el, ++i);
}

template <typename Type>
Array<Type>::Array(Type el) : n_(1), a_(new Type[1]{ el }) {
    //std::cout << "Array(el)\n";
}

template<typename Type>
Array<Type>::Array(const Array& arr) : n_(arr.size()), a_(new Type[arr.size()]) {
    //std::cout << "Array(arr)\n";
    for (size_t i = 0; i < n_; ++i)
        a_[i] = arr.get(i);
}

template<typename Type>
Array<Type>::Array(const Array& left, const Array& right) : n_(left.size() + right.size()), a_(new Type[left.size() + right.size()]) {
    size_t i = 0, j = 0, k = 0;

    while (i < left.size() && j < right.size())
        a_[k++] = (left.get(i) < right.get(j)) ? left.get(i++) : right.get(j++);

    while (i < left.n_)
        a_[k++] = left.get(i++);

    while (j < right.n_)
        a_[k++] = right.get(j++);
}

template<typename Type>
Array<Type>::~Array() {
    //std::cout << "~Array()\n";
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
    if (index > n_ || index < 0) return false;
    a_[index] = value;
    sort();
    return true;
}


template<typename Type>
void Array<Type>::print() const {
    for (size_t i = 0; i < n_; std::cout << a_[i] << " ", ++i);
}

std::size_t operator""_sz(unsigned long long x) { return x; }


int main() {
    Array<int> arr1(4, 9);
    arr1.set(0, -5);
    arr1.set(2, 4);
    arr1.set(3, 1);
    std::cout << "arr1: " << arr1 << "\n";

    Array<int> arr2(3, 7);
    arr2.set(1, -4);
    arr2.set(2, 1);
    std::cout << "arr2: " << arr2 << "\n";

    Array<int> arr3(2, 6);
    std::cout << "arr3: " << arr3 << "\n";

    Array<int> merged1(arr1, arr2);
    std::cout << "Merged arr1 and arr2: " << merged1 << "\n";

    std::cout << "Merge arr1, arr2 and arr3: " << merge(merged1, arr3);
    return 0;
}
