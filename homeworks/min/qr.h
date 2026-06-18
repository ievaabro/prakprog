// The interface for the qr

#pragma once 
#include "matrix.h"

namespace pp {

struct qr {
    matrix Q; // Orthogonal matrix
    matrix R; // Upper triangular matrix

    qr(const matrix& A); // Constructor that computes decomposition

    vector solve(const vector& b) const; // Solves Ax=b
    double det() const; // Determinant
    matrix inverse() const; // Inverse matrix
};

}