#include "qr.h"
#include <cmath>
#include <stdexcept>

namespace pp {

// Gram-Schmidt
qr::qr(const matrix& A) : Q(A), R(A.size2(), A.size2()) { // Decomposition

    int n = Q.size1();
    int m = Q.size2();

    for(int j = 0; j < m; j++){ // Process one column at a time

        // norm
        double norm = 0;
        for(int i = 0; i < n; i++)
            norm += Q(i,j)*Q(i,j);

        norm = std::sqrt(norm); // Computes the column norm

        if(norm == 0) throw std::runtime_error("Matrix is rank deficient"); // Rank check - if column in 0 then the matrix is rank deficient

        R(j,j) = norm; // Store diagonal of R

        // normalize column j
        for(int i = 0; i < n; i++)
            Q(i,j) /= norm; // Normalize column - now the column j has length 1

        // orthogonalize remaining columns
        for(int k = j+1; k < m; k++){ // Remove the component of column k in direction of column j

            double dot = 0;
            for(int i = 0; i < n; i++)
                dot += Q(i,j)*Q(i,k); // Computing the dot product

            R(j,k) = dot;

            for(int i = 0; i < n; i++)
                Q(i,k) -= Q(i,j)*dot; // Subtract projection
        }
    }
}

// Solve Ax = b
vector qr::solve(const vector& b) const {

    int m = R.size2();

    // y = Q^T b
    vector y(m);

    for(int i = 0; i < m; i++){
        y[i] = 0;
        for(int k = 0; k < Q.size1(); k++)
            y[i] += Q(k,i)*b[k]; // Compute y=Q^T b
    }

    vector x(m);

    for(int i = m-1; i >= 0; i--){ // Back substitution (R is upper triangular Rx=y)
        double sum = y[i];

        for(int k = i+1; k < m; k++)
            sum -= R(i,k)*x[k]; 

        x[i] = sum / R(i,i);
    }

    return x;
}

// Determinant
double qr::det() const {
    double d = 1;
    for(int i = 0; i < R.size2(); i++)
        d *= R(i,i);
    return d;
}

// Matrix inverse
matrix qr::inverse() const {

    int n = Q.size1();
    int m = Q.size2();

    matrix B(m,m);

    vector e(n);

    for(int i = 0; i < m; i++){

        // reset e
        for(int j = 0; j < n; j++) e[j] = 0;

        e[i] = 1; // Build unit vectors

        vector x = solve(e); // Solve - gives one columns of the inverse

        for(int k = 0; k < m; k++)
            B(k,i) = x[k]; // Store result
    }

    return B;
}

}