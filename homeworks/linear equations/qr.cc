#include "qr.h"
#include <stdexcept>

namespace pp {

//constructor
qr::qr(const matrix& A)
    : Q(A), R(A.size2(), A.size2())
{
    int m = A.size2();

    for (int i = 0; i < m; i++) {
        double norm = Q[i].norm();
        if (norm == 0)
            throw std::runtime_error("Singular matrix");

        R(i, i) = norm;
        Q[i] /= norm;

        for (int j = i + 1; j < m; j++) {
            R(i, j) = Q[i].dot(Q[j]);
            Q[j] -= Q[i] * R(i, j);
        }
    }
}


vector qr::solve(const vector& b) const {
    int m = R.size1();

    // y = Q^T b
    vector y = Q.transpose() * b;

    // Back substitution
    vector x(m);
    for (int i = m - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < m; j++) {
            x[i] -= R(i, j) * x[j];
        }
        x[i] /= R(i, i);
    }

    return x;
}



double qr::det() const {
    double prod = 1;
    for (int i = 0; i < R.size1(); i++)
        prod *= R(i, i);
    return prod;
}



matrix qr::inverse() const {
    int m = R.size1();
    matrix inv(m, m);

    for (int i = 0; i < m; i++) {
        vector e(m);
        e[i] = 1.0;

        vector col = solve(e);

        for (int j = 0; j < m; j++)
            inv(j, i) = col[j];
    }

    return inv;
}

} // for namespace pp