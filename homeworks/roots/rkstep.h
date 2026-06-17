#pragma once
#include <functional>
#include <tuple>
#include "matrix.h"

std::tuple<pp::vector,pp::vector> rkstep12(
    std::function<pp::vector(double,pp::vector)> f,
    double x,
    pp::vector y,
    double h
);