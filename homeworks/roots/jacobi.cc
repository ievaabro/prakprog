#include <cmath>
#include <functional>

#include "jacobi.h"

pp::matrix jacobian(
    std::function<pp::vector(pp::vector)> f,
    pp::vector x,
    pp::vector fx
){

    int n = x.size();

    pp::matrix J(n,n);

    for(int j=0; j<n; j++){

        double dx = fabs(x[j])*pow(2,-26);

        if(dx == 0) dx = pow(2,-26);

        x[j] += dx;

        pp::vector df = f(x) - fx;

        for(int i=0; i<n; i++){
            J[i,j] = df[i]/dx;
        }

        x[j] -= dx;
    }

    return J;
}