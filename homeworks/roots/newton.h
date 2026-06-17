#ifndef HAVE_NEWTON_H
#define HAVE_NEWTON_H

#include <functional>

// #include "vec.h"
#include "matrix.h"

pp::vector newton(
    std::function<pp::vector(pp::vector)> f,
    pp::vector x,
    double acc = 1e-6,
    double alpha_min = 1e-3,
    int max_iter = 100
);

#endif