#include <iostream>
#include <cmath>
#include <vector>
#include <string>

const double PI = 3.14159265358979323846;

/* error function approximation */
double erf_approx(double x){
    if(x<0) return -erf_approx(-x);
    std::vector<double> a {0.254829592,-0.284496736,1.421413741,-1.453152027,1.061405429};
    double t=1/(1+0.3275911*x);
    double sum=t*(a[0]+t*(a[1]+t*(a[2]+t*(a[3]+t*a[4]))));
    return 1-sum*exp(-x*x);
}

/* Stirling gamma approximation */
double sgamma(double x){
    if(x<0) return PI/sin(PI*x)/sgamma(1-x);
    if(x<9) return sgamma(x+1)/x;
    double lnsgamma = log(2*PI)/2 + (x-0.5)*log(x) - x + (1.0/12)/x - (1.0/360)/(x*x*x) + (1.0/1260)/(x*x*x*x*x);
    return exp(lnsgamma);
}

/* logarithm of gamma */
double lngamma(double x){
    if(x<=0) return NAN;
    if(x<9) return lngamma(x+1)-log(x);
    return x*log(x+1/(12*x-1/(10*x)))-x+log(2*PI/x)/2;
}

int main(int argc, char** argv){
    std::string mode;
    if(argc>2 && std::string(argv[1])=="-mode") mode = argv[2];

    if(mode=="erf"){  // full curve
        for(double x=-3;x<=3;x+=0.05)
            std::cout << x << " " << erf_approx(x) << "\n";
    }
    else if(mode=="erf-tab"){  // tabulated points
        double xtab[] = {-2,-1,-0.5,0,0.5,1,2};
        for(double x : xtab)
            std::cout << x << " " << erf_approx(x) << "\n";
    }
    else if(mode=="gamma"){  // curve
        for(double x=0.1;x<=6;x+=0.05)
            std::cout << x << " " << sgamma(x) << "\n";
    }
    else if(mode=="gamma-tab"){  // factorial points
        for(int n=1;n<=6;n++)
            std::cout << n << " " << tgamma(n) << "\n";
    }
    else if(mode=="lngamma"){  // log gamma
        for(double x=0.1;x<=10;x+=0.05)
            std::cout << x << " " << lngamma(x) << "\n";
    }
}