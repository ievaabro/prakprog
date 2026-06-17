#ifndef HAVE_JACOBIAN_H
#define HAVE_JACOBIAN_H

#include <functional>
#include "matrix.h"

pp::matrix jacobian(
    std::function<pp::vector(pp::vector)> f,
    pp::vector x,
    pp::vector fx
);

#endif