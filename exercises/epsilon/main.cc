#include<limits>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include"approx.h"


int main(){

    // part 1 of 3
    float       f=1.0f; while((float)      (1.0f+f) != 1.0f){f/=2.0f;} f*=2.0f;
    double      d=1.0d; while((double)     (1.0d+d) != 1.0d){d/=2.0d;} d*=2.0d;
    long double l=1.0L; while((long double)(1.0L+l) != 1.0L){l/=2.0L;} l*=2.0L;

    std::cout << "\ncomputed ('experimental') epsilon: \n";
    std::printf("float: eps = %g\n",f);
    std::printf("double: eps = %g\n",d);
    std::printf("long double: eps = %Lg\n",l);

    std::cout << "\nsystem epsilon: \n";
    std::cout << "float: eps = " << std::numeric_limits<float>::epsilon() << "\n";
    std::cout << "double: eps = " << std::numeric_limits<double>::epsilon() << "\n";
    std::cout << "long double: eps = " << std::numeric_limits<long double>::epsilon() << "\n";

    std::cout << "\ncomparison (float):\n";
    std::cout << "computed eps - theoretical eps = " << f - std::pow(2.0, -23) << "\n";

    std::cout << "\ncomparison (double):\n";
    std::cout << "computed eps - theoretical eps = " << d - std::pow(2.0, -52) << "\n";

    // part 2 of 3
    double epsilon=std::pow(2,-52);
    double tiny=epsilon/2;
    double a=1+tiny+tiny;
    double b=tiny+tiny+1;
    std::cout << "a==b ? " << (a==b ? "true":"false") << "\n";
    std::cout << "a>1  ? " << (a>1  ? "true":"false") << "\n";
    std::cout << "b>1  ? " << (b>1  ? "true":"false") << "\n";
    std::cout << "\nTiny is smaller than machine epsilon, and is lost due to rounding in the case of a. In case b, tiny + tiny is found first, so nothing is lost due to rounding, and epsilon (= tiny + tiny) is kept when adding to 1. \n";

    std::cout << std::fixed << std::setprecision(17);
    std::cout << "tiny = " << tiny << "\n";
    std::cout << "a: 1+tiny+tiny=" << a << "\n";
    std::cout << "b: tiny+tiny+1=" << b << "\n";

    // part 3 of 3
    double d1 = 0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1;
    double d2 = 8*0.1;

    std::cout << "\nd1==d2? " << (d1==d2 ? "true":"false") << "\n"; 
    std::cout << std::fixed << std::setprecision(17);
    std::cout << "d1=" << d1 << "\n";
    std::cout << "d2=" << d2 << "\n";

    std::cout << "approx(d1, d2) ? " << (approx(d1, d2) ? "true" : "false") << "\n";
}