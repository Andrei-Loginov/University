#include "String.h"

String::String(const char* s) {
	if (s == nullptr) {
		n = -1;
		str = 0;
	}
	else {
		n = strlen(s);
		str = new char[n + 1]; 
		str[n] = '\0';
		strcpy(str, s);
	}
}

String::String(const String& s): n(s.n), str(new char[s.n + 1]) {
	strcpy(str, s.str);
}

String::String(String&& s) : n(s.n), str(s.str){
	s.n = 0;
	s.str = nullptr;
}

const char* String::c_str() const noexcept{
	return str;
}

char& String::operator[](int i) {
	std::cout << "Size = " << n << "\ni = " << i << "\n";
	assert(i >= 0 && i < n);
	return str[i];
}

const char& String::operator[](int i) const {
	return str[i];
}

String& String::operator=(String s) {
	this->swap(s);
	return* this;
}

String& String::operator+=(const String& s) {
	char* temp = new char[n + s.n + 1];
	n += s.n;
	strcpy(temp, str);
	strcat(temp, s.str);
	delete[]str;
	str = temp;
	return *this;
}

String String::operator()(int i, int j) {
	assert((i < j) && (i >= 0 && i <= n) && (j >= 0 && j <= n));
	char* temp = new char[j - i + 1];
	strncpy(temp, str + i, j - i);
	temp[j - i] = '\0';
	String ans;
	ans.str = temp;
	ans.n = j - i;
	return ans;
}

bool operator==(const String& lhs, const String& rhs) {
	return lhs.IsEqual(rhs);
}

bool operator<(const String& lhs, const String& rhs) {
	return lhs.IsLessThan(rhs);
}

bool operator!=(const String& lhs, const String& rhs) {
	return !(lhs == rhs);
}

bool operator>(const String& lhs, const String& rhs) {
	return (rhs < lhs);
}

bool operator<=(const String& lhs, const String& rhs) {
	return !(lhs > rhs);
}

bool operator>=(const String& lhs, const String& rhs) {
	return !(lhs < rhs);
}

String operator+(const String& lhs, const String& rhs) {
	String temp(lhs);
	temp += rhs;
	return temp;
}

std::ostream& operator<<(std::ostream& stream, const String& s) {
	stream << s.str;
	return stream;
}

std::istream& operator>>(std::istream& stream, String& s) {
	int size = 1, k, multiplier = 2;
	char* buff1 = new char[size + 1], *buff2, c = 0;
	buff1[size] = '\0';

	for (stream.get(c), k = 0; c != ' ' && c != '\n'; stream.get(c), ++k) {
		buff1[k] = c;
		if (k + 1 == size) {
			buff2 = new char[(size *= multiplier) + 1];
			buff2[size] = '\0';
			strcpy(buff2, buff1);
			delete[]buff1;
			buff1 = buff2;
		}
	}
	buff1[k] = '\0';
	
	delete[]s.str;
	s.n = k;
	s.str = new char[k + 1];
	strcpy(s.str, buff1);
	return stream;
}

void String::swap(String& other) noexcept{
	std::swap(other.str, str);
	std::swap(other.n, n);
}

void swap(String& lhs, String& rhs) {
	String tmp(std::move(lhs));
	lhs = std::move(rhs);
	rhs = std::move(tmp);
}