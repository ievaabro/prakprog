#pragma once
#include <functional>
#include <vector>

#include "vec.h"

std::tuple<std::vector<double>,std::vector<vector>> driver(
    std::function<vector(double,vector)> F,
    double a,
    double b,
    vector yinit,
    double h = 0.125,
    double acc = 0.01,
    double eps = 0.01
);