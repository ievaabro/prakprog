#include<iostream>
#include<cmath>
#include<numbers>
#include"sfuns.h"
#include<limits>
#include<complex>


namespace sfuns{
using complex=std::complex<double>;
constexpr complex I = complex(0,1);

void print_things() {
	double sqrt2=std::sqrt(2.0);
	std::cout << "sqrt(2) = " << sqrt2 << std::endl;
	double fifth= std::pow(2.0, 1.0/5);
	std::cout << "2^(1/5) = " << fifth << std::endl;
	double epi = std::pow(std::numbers::e, std::numbers::pi);
	std::cout << "e^pi = " << epi << std::endl;
	double pie = std::pow(std::numbers::pi, std::numbers::e);
	std::cout << "pi^e = " << pie << std::endl;
	std::cout << "log(I)=" << std::log(I)   <<"\n";
    std::cout << "   I^I=" << std::pow(I,I) <<"\n";
    std::cout << "   π^I=" << std::pow(std::numbers::pi,I) <<"\n";
    std::cout << "   E^I=" << std::pow(std::numbers::e,I) <<"\n";
}

constexpr double PI = std::numbers::pi; // c++20
// constexpr double PI = 3.14159265358979323846; // pre- c++20
double fgamma(double x){
	if(x<0)return PI/std::sin(PI*x)/fgamma(1-x);
	if(x<9)return fgamma(x+1)/x;
	double lnfgamma=x*std::log(x+1/(12*x-1/x/10))-x+std::log(2*PI/x)/2;
	return std::exp(lnfgamma);
	}

constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
double lnfgamma(double x){
	if(x <= 0) return NaN; // Not-a-Number
	if(x < 9) return lnfgamma(x+1) - std::log(x);
	double lnfgamma=x*std::log(x+1/(12*x-1/x/10))-x+std::log(2*PI/x)/2;
	return lnfgamma;
}

}