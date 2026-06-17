#pragma once

#include <vector>
#include <functional>

std::function<double(double)>
make_qspline(vector x, vector y);