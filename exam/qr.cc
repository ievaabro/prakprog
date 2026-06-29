#include "qr.h"
#include <stdexcept>
#include <cmath>

namespace pp {

qr::qr(const matrix& A)
    : Q(A), R(A.size2(), A.size2())
{
    int n = A.size2();

    for (int i = 0; i < n; i++) {

        
        double norm = 0.0;
        for (int k = 0; k < Q.size1(); k++)
            norm += Q(k, i) * Q(k, i);

        norm = std::sqrt(norm);

        if (norm == 0)
            throw std::runtime_error("Singular matrix");

        R(i, i) = norm;

        for (int k = 0; k < Q.size1(); k++)
            Q(k, i) /= norm;

        
        for (int j = i + 1; j < n; j++) {

            double dot = 0.0;

            for (int k = 0; k < Q.size1(); k++)
                dot += Q(k, i) * Q(k, j);

            R(i, j) = dot;

            for (int k = 0; k < Q.size1(); k++)
                Q(k, j) -= Q(k, i) * dot;
        }
    }
}

// --------------------------------------------------

vector qr::solve(const vector& b) const {

    int n = R.size1();

    vector y(n);

    // y = Q^T b
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int k = 0; k < Q.size1(); k++)
            sum += Q(k, i) * b[k];
        y[i] = sum;
    }

    // back substitution
    vector x(n);

    for (int i = n - 1; i >= 0; i--) {
        double sum = y[i];

        for (int j = i + 1; j < n; j++)
            sum -= R(i, j) * x[j];

        x[i] = sum / R(i, i);
    }

    return x;
}

// --------------------------------------------------

double qr::det() const {
    double prod = 1.0;
    for (int i = 0; i < R.size1(); i++)
        prod *= R(i, i);
    return prod;
}

// --------------------------------------------------

matrix qr::inverse() const {

    int n = R.size1();
    matrix inv(n, n);

    for (int i = 0; i < n; i++) {

        vector e(n);
        e[i] = 1.0;

        vector col = solve(e);

        for (int j = 0; j < n; j++)
            inv(j, i) = col[j];
    }

    return inv;
}

} // namespace pp