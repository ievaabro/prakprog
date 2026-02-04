#include<iostream>
#include<cmath>
#include<numbers>
#include"sfuns.h"

namespace sfuns{

void print_things() {
	double sqrt2=std::sqrt(2.0);
	std::cout << "sqrt(2) = " << sqrt2 << std::endl;
	double fifth= std::pow(2.0, 1.0/5);
	std::cout << "2^(1/5) = " << fifth << std::endl;
	double epi = std::pow(std::numbers::e, std::numbers::pi);
	std::cout << "e^pi = " << epi << std::endl;
	double pie = std::pow(std::numbers::pi, std::numbers::e);
	std::cout << "pi^e = " << pie << std::endl;
}
}