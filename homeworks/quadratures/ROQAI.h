// #ifndef ROQAI_H
// #define ROQAI_H

#pragma once

#include <cmath>
#include <functional>

// std::numeric_limits<double>::quiet_NaN()

double integrate(
    std::function<double(double)> f,
    double a,
    double b,
    double acc = 1e-3,
    double eps = 1e-3,
    double f2 = NAN,
    double f3 = NAN
);

double integrate_cc(
    std::function<double(double)> f,
    double a,
    double b,
    double acc = 1e-3,
    double eps = 1e-3
);

double integrate_inf(
    std::function<double(double)> f,
    double a,
    double b,
    double acc = 1e-3,
    double eps = 1e-3
);

// #endif