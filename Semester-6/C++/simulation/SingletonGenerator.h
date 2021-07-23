#pragma once
#include <random>

/**
* Данный класс позволяет использовать один экземпляр ГПСЧ на всю программу
*/

class SingletonGenerator{
	static std::mt19937 mersennetwister;
public:
	static std::mt19937& get_mt();
};

