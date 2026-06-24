#include <iostream>
#include <random>
#include <cmath>

#include "matrix.h"
#include "lu.h"

using namespace pp;

// random matrix
matrix random_matrix(int n) {
    matrix A(n, n);

    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (int j = 0; j < n; j++)
        for (int i = 0; i < n; i++)
            A(i, j) = dist(gen);

    return A;
}

// approximate matrix comparison
bool approx_matrix(const matrix& A, const matrix& B,
                   double acc = 1e-6, double eps = 1e-6) {

    if (A.size1() != B.size1() || A.size2() != B.size2())
        return false;

    for (int i = 0; i < A.size1(); i++) {
        for (int j = 0; j < A.size2(); j++) {

            double a = A(i, j);
            double b = B(i, j);

            if (std::abs(a - b) > acc &&
                std::abs(a - b) > eps * std::max(std::abs(a), std::abs(b)))
                return false;
        }
    }

    return true;
}

// identity matrix
matrix identity(int n) {
    matrix I(n, n);

    for (int i = 0; i < n; i++)
        I(i, i) = 1.0;

    return I;
}

// check lower triangular with ones on diagonal
bool check_L(const matrix& L, double tol = 1e-6) {

    int n = L.size1();

    for (int i = 0; i < n; i++) {

        if (std::abs(L(i, i) - 1.0) > tol)
            return false;

        for (int j = i + 1; j < n; j++) {
            if (std::abs(L(i, j)) > tol)
                return false;
        }
    }

    return true;
}

// check upper triangular
bool check_U(const matrix& U, double tol = 1e-6) {

    int n = U.size1();

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (std::abs(U(i, j)) > tol)
                return false;
        }
    }

    return true;
}

int main(int argc, char** argv)
{
    int n = 5;

    if(argc > 2 && std::string(argv[1]) == "-size")
        n = std::stoi(argv[2]);

    std::cout << "Generating matrix A...\n";
    matrix A = random_matrix(n);

    std::cout << "Computing LU decomposition...\n";
    lu LU(A);

    // check L structure
    bool ok1 = check_L(LU.L);

    std::cout << "L lower triangular with unit diagonal: "
              << (ok1 ? "OK" : "FAIL") << "\n";

    // check U structure
    bool ok2 = check_U(LU.U);

    std::cout << "U upper triangular: "
              << (ok2 ? "OK" : "FAIL") << "\n";

    // check LU = A
    matrix LUmat = LU.L * LU.U;

    bool ok3 = approx_matrix(LUmat, A);

    std::cout << "LU = A: "
              << (ok3 ? "OK" : "FAIL") << "\n";

    // solve Ax=b
    vector b(n);

    for (int i = 0; i < n; i++)
        b[i] = (double)rand() / RAND_MAX;

    vector x = LU.solve(b);
    vector Ax = A * x;

    double err = 0.0;

    for (int i = 0; i < n; i++)
        err += std::abs(Ax[i] - b[i]);

    std::cout << "Solve Ax=b error: "
              << err << "\n";

    // determinant
    std::cout << "det(A): "
              << LU.det() << "\n";

    // inverse
    matrix Ainv = LU.inverse();

    matrix Icheck = A * Ainv;

    bool ok4 = approx_matrix(Icheck, identity(n));

    std::cout << "A * A^-1 = I: "
              << (ok4 ? "OK" : "FAIL") << "\n";

    if (ok1 && ok2 && ok3 && ok4)
        std::cout << "\nALL TESTS PASSED\n";
    else
        std::cout << "\nSOME TESTS FAILED\n";

    return 0;
}