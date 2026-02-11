#include"sfuns.h"
#include<iostream>
#include<cmath>

int main(){
    sfuns::print_things();
    //sfuns::fgamma();

    double i = 1;
    while (i <= 10){
        std::cout << "\nfgamma(" << i << ") = " << sfuns::fgamma(i) << std::endl;
        std::cout << "(from cmath) tgamma(" << i << ") = " << std::tgamma(i) << std::endl;
        std::cout << "difference between fgamma and tgamma: fgamma(" << i << ") - tgamma(" << i << ") = " << sfuns::fgamma(i) - std::tgamma(i) << " so the difference is very small, and our approximation is good :)" << std::endl;
        std::cout << "lnfgamma(" << i << ") = " << sfuns::lnfgamma(i) << std::endl;
        i++;
    }

    
    return 0;
}
