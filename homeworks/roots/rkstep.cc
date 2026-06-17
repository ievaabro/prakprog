#include "rkstep.h"

// namespace pp {

std::tuple<pp::vector,pp::vector> rkstep12(
    std::function<pp::vector(double,pp::vector)> f,
    double x, pp::vector y, double h)
{
    // Euler slope
    pp::vector k0 = f(x,y);

    // Midpoint slope
    pp::vector k1 = f(x + h/2, y + k0*(h/2));

    // Higher-order estimate (2nd order)
    pp::vector yh = y + k1*h;

    // Error estimate:
    // difference between midpoint and Euler
    pp::vector err = (k1 - k0)*h;

    return {yh, err};
}

// }