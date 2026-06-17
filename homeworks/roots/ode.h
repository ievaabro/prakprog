// #pragma once
// #include <functional>
// // #include <vec>

// #include "vec.h"

// std::tuple<vec<double>,vec<vec>> driver(
//     std::function<vec(double,vec)> F,
//     double a,
//     double b,
//     vec yinit,
//     double h = 0.125,
//     double acc = 0.01,
//     double eps = 0.01
// );

#pragma once

#include <functional>
#include <tuple>
#include <vector>
#include "matrix.h"

// #include "vec.h"

std::tuple<
    std::vector<double>,
    std::vector<pp::vector>
>
driver(
    std::function<pp::vector(double, pp::vector)> F,
    double a,
    double b,
    pp::vector yinit,
    double h = 0.125,
    double acc = 0.01,
    double eps = 0.01
);