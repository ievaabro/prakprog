#include <cmath>
#include <functional>

#include "newton.h"
#include "jacobi.h"
#include "matrix.h"
#include "qr.h"

pp::vector newton(
    std::function<pp::vector(pp::vector)> f,
    pp::vector x,
    double acc,
    double alpha_min,
    int max_iter
){

    pp::vector fx = f(x);

    for(int iter=0; iter<max_iter; iter++){

        if(fx.norm() < acc) break;

        pp::matrix J = jacobian(f,x,fx);

        pp::qr qr(J);
        pp::vector Dx = qr.solve(-fx);

        if(Dx.norm() < pow(2,-26)) break;

        double alpha = 1.0;

        pp::vector z;
        pp::vector fz;

        while(true){

            z = x + alpha*Dx;

            fz = f(z);

            if(fz.norm() < fx.norm()) break;

            if(alpha < alpha_min) break;

            alpha /= 2.0;
        }

        x = z;
        fx = fz;
    }

    return x;
}