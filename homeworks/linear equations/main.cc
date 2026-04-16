#include <iostream>
#include <random>
#include <cmath>

#include "matrix.h"
#include "qr.h"

using namespace pp;

//random matrix
matrix random_matrix(int n) {
    matrix A(n, n);

    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (int j = 0; j < n; j++)
        for (int i = 0; i < n; i++)
            A(i, j) = dist(gen);

    return A;
}

//approx
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

matrix identity(int n) {
    matrix I(n, n);
    for (int i = 0; i < n; i++)
        I(i, i) = 1.0;
    return I;
}

//main test 
int main() {

    int n = 5;

    std::cout << "Generating matrix A...\n";
    matrix A = random_matrix(n);

    std::cout << "Computing QR...\n";
    qr QR(A);

    //  Q^T Q = I
    matrix QtQ = QR.Q.transpose() * QR.Q;
    bool ok1 = approx_matrix(QtQ, identity(n));

    std::cout << "Q^T Q = I: " << (ok1 ? "OK" : "FAIL") << "\n";

    //  QR = A 
    matrix QRmat = QR.Q * QR.R;
    bool ok2 = approx_matrix(QRmat, A);

    std::cout << "QR = A: " << (ok2 ? "OK" : "FAIL") << "\n";

    // solve Ax = b 
    vector b(n);
    for (int i = 0; i < n; i++)
        b[i] = (double)rand() / RAND_MAX;

    vector x = QR.solve(b);
    vector Ax = A * x;

    double err = 0.0;
    for (int i = 0; i < n; i++)
        err += std::abs(Ax[i] - b[i]);

    std::cout << "Solve Ax=b error: " << err << "\n";

    //determinant
    std::cout << "det(A): " << QR.det() << "\n";

    // inverse
    matrix Ainv = QR.inverse();
    matrix Icheck = A * Ainv;

    bool ok3 = approx_matrix(Icheck, identity(n));

    std::cout << "A * A^-1 = I: " << (ok3 ? "OK" : "FAIL") << "\n";

    if (ok1 && ok2 && ok3)
        std::cout << "\nALL TESTS PASSED\n";
    else
        std::cout << "\nSOME TESTS FAILED\n";

    return 0;
}