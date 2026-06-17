#pragma once
#include <functional>
#include <tuple>
#include "vec.h"

std::tuple<vector,vector> rkstep12(
    std::function<vector(double,vector)> f,
    double x,
    vector y,
    double h
);