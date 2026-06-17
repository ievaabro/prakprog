#include "rkstep.h"

// namespace pp {

std::tuple<vector,vector> rkstep12(
    std::function<vector(double,vector)> f,
    double x, vector y, double h)
{
    // Euler slope
    vector k0 = f(x,y);

    // Midpoint slope
    vector k1 = f(x + h/2, y + k0*(h/2));

    // Higher-order estimate (2nd order)
    vector yh = y + k1*h;

    // Error estimate:
    // difference between midpoint and Euler
    vector err = (k1 - k0)*h;

    return {yh, err};
}

// }