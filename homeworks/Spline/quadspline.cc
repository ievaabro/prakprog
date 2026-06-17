#include "vec.h"
#include <functional>
#include <cassert>
#include "quadspline.h"

std::function<double(double)>
make_qspline(vector x, vector y)
{
    int n = x.size();

    vector b(n), c(n);

    // a_i = y_i, implicit

    // --- compute coefficients ---
    b[0] = (y[1] - y[0]) / (x[1] - x[0]);

    for(int i = 0; i < n - 1; i++) {

        double dx = x[i+1] - x[i];
        assert(dx > 0);

        // enforce continuity of derivative
        b[i+1] = 2*(y[i+1] - y[i]) / dx - b[i];

        c[i] = (b[i+1] - b[i]) / (2*dx);
    }

    // last interval curvature (optional safe fallback)
    c[n-1] = 0;

    // // --- returned spline function ---
    // auto spline = [=](double z) mutable -> double {

    //     // find interval
    //     int i = 0;
    //     while(i < n-2 && z > x[i+1])
    //         i++;

    //     double dx = z - x[i];

    //     return y[i] + b[i]*dx + c[i]*dx*dx;
    // };

    // --- MOVE CAPTURE LAMBDA ---
    return [x = std::move(x),
            y = std::move(y),
            b = std::move(b),
            c = std::move(c),
            n](double z) -> double {

        int i = 0;

        while(i < n-2 && z > x[i+1])
            i++;

        double dx = z - x[i];

        return y[i] + b[i]*dx + c[i]*dx*dx;
    };
}