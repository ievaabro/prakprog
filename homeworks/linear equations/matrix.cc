// #include <vector>
// #include <iostream>
// #include <iomanip>
// #include <stdexcept>
// #include "matrix.h"




// namespace pp {

// matrix::matrix(int n, int m) : cols(m, vector(n)) {}

// pp::matrix::matrix(const matrix& other)
//     : cols(other.cols)
// {}

// pp::matrix::matrix(matrix&& other) noexcept
//     : cols(std::move(other.cols))
// {}


// int matrix::size1() const {
//     return cols.empty() ? 0 : cols[0].size();
// }

// int matrix::size2() const {
//     return cols.size();
// }

// double& matrix::operator()(int i, int j) {
//     return cols[j][i];
// }

// const double& matrix::operator()(int i, int j) const {
//     return cols[j][i];
// }

// vector& matrix::operator[](int j) {
//     return cols[j];
// }

// const vector& matrix::operator[](int j) const {
//     return cols[j];
// }



// void matrix::setid() {
//     if (size1() != size2())
//         throw std::runtime_error("non-square matrix");

//     for (int i = 0; i < size1(); i++) {
//         for (int j = 0; j < size2(); j++) {
//             (*this)(i,j) = (i == j) ? 1.0 : 0.0;
//         }
//     }
// }


// matrix matrix::transpose() const {
//     matrix R(size2(), size1());
//     for (int i = 0; i < size1(); i++)
//         for (int j = 0; j < size2(); j++)
//             R(j,i) = (*this)(i,j);
//     return R;
// }



// matrix& matrix::operator+=(const matrix& B) {
//     for (int j = 0; j < size2(); j++)
//         cols[j] += B[j];
//     return *this;
// }

// matrix& matrix::operator-=(const matrix& B) {
//     for (int j = 0; j < size2(); j++)
//         cols[j] -= B[j];
//     return *this;
// }

// matrix& matrix::operator*=(double c) {
//     for (auto& col : cols)
//         col *= c;
//     return *this;
// }

// matrix& matrix::operator/=(double c) {
//     for (auto& col : cols)
//         col /= c;
//     return *this;
// }


// void matrix::print(std::string s) const {
//     std::cout << s << "\n";
//     std::cout << std::fixed << std::setprecision(4);

//     for (int i = 0; i < size1(); i++) {
//         for (int j = 0; j < size2(); j++)
//             std::cout << std::setw(10) << (*this)(i,j);
//         std::cout << "\n";
//     }
// }


// matrix operator+(matrix A, const matrix& B) {
//     return A += B;
// }

// matrix operator-(matrix A, const matrix& B) {
//     return A -= B;
// }

// matrix operator*(const matrix& A, const matrix& B) {
//     if (A.size2() != B.size1())
//         throw std::invalid_argument("size mismatch");

//     matrix R(A.size1(), B.size2());

//     for (int j = 0; j < B.size2(); j++) {
//         for (int k = 0; k < A.size2(); k++) {
//             double Bkj = B(k,j);
//             for (int i = 0; i < A.size1(); i++) {
//                 R(i,j) += A(i,k) * Bkj;
//             }
//         }
//     }

//     return R;
// }

// vector operator*(const matrix& A, const vector& v) {
//     vector r(A.size1());

//     for (int j = 0; j < A.size2(); j++) {
//         double vj = v[j];
//         for (int i = 0; i < A.size1(); i++)
//             r[i] += A(i,j) * vj;
//     }

//     return r;
// }

// } // namespace pp



#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include "matrix.h"

namespace pp {

//constructors
matrix::matrix(int n, int m)
    : cols(m, vector(n)) {}

matrix::matrix(const matrix& other)
    : cols(other.cols) {}

matrix::matrix(matrix&& other)
    : cols(std::move(other.cols)) {}

matrix& matrix::operator=(const matrix& other) {
    cols = other.cols;
    return *this;
}

matrix& matrix::operator=(matrix&& other) {
    cols = std::move(other.cols);
    return *this;
}


int matrix::size1() const {
    return cols.empty() ? 0 : cols[0].size();
}

int matrix::size2() const {
    return cols.size();
}

//operators
double& matrix::operator()(int i, int j) {
    return cols[j][i];
}

const double& matrix::operator()(int i, int j) const {
    return cols[j][i];
}

vector& matrix::operator[](int j) {
    return cols[j];
}

const vector& matrix::operator[](int j) const {
    return cols[j];
}


void matrix::setid() {
    if (size1() != size2())
        throw std::runtime_error("non-square matrix");

    for (int i = 0; i < size1(); i++)
        for (int j = 0; j < size2(); j++)
            (*this)(i, j) = (i == j) ? 1.0 : 0.0;
}


matrix matrix::transpose() const {
    matrix R(size2(), size1());

    for (int i = 0; i < size1(); i++)
        for (int j = 0; j < size2(); j++)
            R(j, i) = (*this)(i, j);

    return R;
}

matrix& matrix::operator+=(const matrix& B) {
    for (int j = 0; j < size2(); j++)
        cols[j] += B[j];
    return *this;
}

matrix& matrix::operator-=(const matrix& B) {
    for (int j = 0; j < size2(); j++)
        cols[j] -= B[j];
    return *this;
}

matrix& matrix::operator*=(double c) {
    for (auto& col : cols)
        col *= c;
    return *this;
}

matrix& matrix::operator/=(double c) {
    if (c == 0)
        throw std::runtime_error("division by zero");

    for (auto& col : cols)
        col /= c;

    return *this;
}


void matrix::print(std::string s) const {
    std::cout << s << "\n";
    std::cout << std::fixed << std::setprecision(4);

    for (int i = 0; i < size1(); i++) {
        for (int j = 0; j < size2(); j++)
            std::cout << std::setw(10) << (*this)(i, j);
        std::cout << "\n";
    }
}


matrix operator+(matrix A, const matrix& B) {
    return A += B;
}

matrix operator-(matrix A, const matrix& B) {
    return A -= B;
}

matrix operator*(const matrix& A, const matrix& B) {
    if (A.size2() != B.size1())
        throw std::invalid_argument("matrix size mismatch");

    matrix R(A.size1(), B.size2());

    for (int j = 0; j < B.size2(); j++) {
        for (int k = 0; k < A.size2(); k++) {
            double Bkj = B(k, j);
            for (int i = 0; i < A.size1(); i++) {
                R(i, j) += A(i, k) * Bkj;
            }
        }
    }

    return R;
}

vector operator*(const matrix& A, const vector& v) {
    vector r(A.size1());

    for (int j = 0; j < A.size2(); j++) {
        double vj = v[j];
        for (int i = 0; i < A.size1(); i++)
            r[i] += A(i, j) * vj;
    }

    return r;
}

} // for namespace pp