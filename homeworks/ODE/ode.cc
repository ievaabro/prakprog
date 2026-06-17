#include <cmath>
#include <algorithm>

#include "ode.h"
#include "rkstep.h"

std::tuple<std::vector<double>,std::vector<vector>> driver(
    std::function<vector(double,vector)> F,
    double a,
    double b,
    vector yinit,
    double h,
    double acc,
    double eps
){
    double x = a;
    vector y = yinit;

    std::vector<double> xlist;
    xlist.push_back(x);

    std::vector<vector> ylist;
    ylist.push_back(y);

    do{

        if(x >= b)
            return std::make_tuple(xlist,ylist);

        if(x + h > b)
            h = b - x;

        auto [yh,dy] = rkstep12(F,x,y,h);

        double tol =
            (acc + eps*yh.norm()) * std::sqrt(h/(b-a));

        double err = dy.norm();

        if(err <= tol){
            x += h;
            y = yh;

            xlist.push_back(x);
            ylist.push_back(y);
        }

        if(err > 0)
            h *= std::min(
                std::pow(tol/err,0.25)*0.95,
                2.0
            );
        else
            h *= 2;

        const double hmin = 1e-4;
        const double hmax = 0.2;

        if(h < hmin) h = hmin;
        if(h > hmax) h = hmax;

    }while(true);
}