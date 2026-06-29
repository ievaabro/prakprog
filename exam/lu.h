#pragma once
#include "matrix.h"

namespace pp {

class lu {
public:

    matrix L;
    matrix U;

    lu(const matrix& A);

    vector solve(const vector& b) const;

    double det() const;

    matrix inverse() const;

private:
    std::vector<int> P; 
};

} // namespace pp

