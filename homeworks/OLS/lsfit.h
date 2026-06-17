#pragma once
#include <vector>
#include <functional>
#include <tuple>

#include "matrix.h"
#include "vector.h"
#include "qr.h"

using func = std::function<double(double)>;

std::tuple<pp::vector,pp::matrix>
lsfit(
    const std::vector<func>& fs,
    const pp::vector& x,
    const pp::vector& y,
    const pp::vector& dy
);