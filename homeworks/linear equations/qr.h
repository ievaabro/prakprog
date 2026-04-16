#pragma once
#include "matrix.h"

namespace pp {

struct qr {
    matrix Q;
    matrix R;

    // constructor
    qr(const matrix& A);

    // methods? 
    vector solve(const vector& b) const;
    double det() const;
    matrix inverse() const;
};

} // for namespace pp