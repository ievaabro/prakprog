#include "lu.h"
#include <stdexcept>
#include <cmath>

namespace pp {

// LU decomposition (Doolittle, no pivoting)
lu::lu(const matrix& A)
    : L(A.size1(), A.size2()),
      U(A)
{
    int n = A.size1();

    for (int i = 0; i < n; i++)
        L(i, i) = 1.0;

    for (int k = 0; k < n - 1; k++) {

        double pivot = U(k, k);

        if (std::abs(pivot) < 1e-12)
            throw std::runtime_error("Zero pivot encountered");

        for (int i = k + 1; i < n; i++) {

            double Uki = U(i, k);
            double factor = Uki / pivot;

            L(i, k) = factor;

            for (int j = k; j < n; j++) {
                U(i, j) -= factor * U(k, j);
            }
        }
    }
}


// Solve Ax=b
vector lu::solve(const vector& b) const {

    int n = L.size1();

    // Forward substitution Ly=b
    vector y(n);

    for (int i = 0; i < n; i++) {

        double sum = b[i];

        for (int j = 0; j < i; j++)
            sum -= L(i, j) * y[j];

        y[i] = sum;
    } 

    // Back substitution Ux=y
    vector x(n);

    for (int i = n - 1; i >= 0; i--) {

        double sum = y[i];

        for (int j = i + 1; j < n; j++)
            sum -= U(i, j) * x[j];

        x[i] = sum / U(i, i);
    }

    return x;
}


// Determinant
double lu::det() const {

    double prod = 1.0;

    int n = U.size1();
    for (int i = 0; i < n; i++)
        prod *= U(i, i);

    return prod;
}


// Inverse matrix
matrix lu::inverse() const {

    int n = U.size1();

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