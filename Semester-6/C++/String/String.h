#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>

class String {
	char* str;
	int n;
	bool IsEqual(const String& S) const { return (strcmp(str, S.str) == 0); }
	bool IsLessThan(const String& S) const { return (strcmp(str, S.str) < 0); }
public:
	int size() const { return n; };
	String() { n = -1; str = 0; };
	explicit String(int nstr) { n = nstr < 0 ? 0 : nstr; str = new char[n + 1]; str[n] = 0; }
	String(const char* s);
	String(const String&);
	String(String&&);
	~String() { delete[] str; };
	const char* c_str() const noexcept;
	void swap(String& other) noexcept;
	friend void swap(String& lhs, String& rhs);
	char& operator[](int i);
	const char& operator[](int i) const;
	String& operator=(String);
	String& operator+=(const String&);
	String operator()(int i, int j);
	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator<(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);
	friend bool operator>(const String& lhs, const String& rhs);
	friend bool operator<=(const String& lhs, const String& rhs);
	friend bool operator>=(const String& lhs, const String& rhs);
	friend String operator+(const String& lhs, const String& rhs);
	friend std::ostream& operator<<(std::ostream& stream, const String& s);
	friend std::istream& operator>>(std::istream& stream, String& s);
};

