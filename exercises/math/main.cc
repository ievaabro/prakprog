#include"sfuns.h"
#include<iostream>

int main(){
    sfuns::print_things();
    //sfuns::fgamma();

    double i = 1;
    while (i <= 10){
        std::cout << "fgamma(" << i << ") = " << sfuns::fgamma(i) << std::endl;
        std::cout << "lnfgamma(" << i << ") = " << sfuns::lnfgamma(i) << std::endl;
        i++;
    }

    
    return 0;
}
