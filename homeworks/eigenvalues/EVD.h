#pragma once
#include <tuple>
#include "matrix.h"
#include "vec.h"

namespace pp {
    std::tuple<pp::vector, pp::matrix> jacobi(pp::matrix A);

    void timesJ(pp::matrix& A, int p, int q, double theta);
    void Jtimes(pp::matrix& A, int p, int q, double theta);
}