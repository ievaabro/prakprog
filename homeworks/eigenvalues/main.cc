#include <iostream>
#include <random>
#include <string>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <cmath>

#include "matrix.h"
#include "EVD.h"

using namespace pp;

// Random symmetric matrices
pp::matrix random_symmetric_matrix(int n) {
    pp::matrix A(n,n);
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(0.0,1.0);

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {

            double x = dist(rng);

            A(i,j) = x;
            A(j,i) = x;
        }
    }
    return A;
}



// Matrix comparison
bool approx_equal(const pp::matrix& A, const pp::matrix& B, double tol = 1e-8) {
    for (int i = 0; i < A.size1(); i++) {
        for (int j = 0; j < A.size2(); j++) {
            if (std::abs(A(i,j) - B(i,j)) > tol) return false;
        }
    }
    return true;
}    

// Transpose function

pp::matrix transpose(const pp::matrix& M) {
    pp::matrix T(M.size2(), M.size1());
    for (int i = 0; i < M.size1(); i++)
        for (int j = 0; j < M.size2(); j++)
            T(j,i) = M(i,j);
    return T;
}

pp::matrix identity_matrix(int n) {
    pp::matrix I(n, n);  // adjust if your constructor differs

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            I(i,j) = (i == j) ? 1.0 : 0.0;
        }
    }

    return I;
}

double ground_state_energy(double rmax, double dr) {
    int npoints = (int)(rmax / dr) - 1;

    pp::vector r(npoints);
    for (int i = 0; i < npoints; i++) {
        r[i] = dr * (i + 1);
    }

    pp::matrix H(npoints, npoints);

    double coeff = -0.5 / (dr * dr);

    for (int i = 0; i < npoints - 1; i++) {
        H(i,i)     = -2 * coeff;
        H(i,i+1)   =  1 * coeff;
        H(i+1,i)   =  1 * coeff;
    }

    H(npoints-1, npoints-1) = -2 * coeff;

    for (int i = 0; i < npoints; i++) {
        H(i,i) += -1.0 / r[i];
    }

    auto [eH, VH] = jacobi(H);

    return eH[0]; // ground state
}

// main program
int main(){ 
    using namespace std;
    using namespace pp;

    // 1. Create a symmetric test matrix
    matrix A(3,3);

    A(0,0)=4;  A(0,1)=1;  A(0,2)=1;
    A(1,0)=1;  A(1,1)=3;  A(1,2)=0;
    A(2,0)=1;  A(2,1)=0;  A(2,2)=2;

    cout << "Input matrix A:\n";
    A.print(); 
    
    // 2. Run Jacobi diagonalization
    auto [wA, VA] = jacobi(A);

    // 3. Print eigenvalues
    cout << "\nEigenvalues:\n";
    for(int i=0;i<wA.size();i++){
        cout << wA[i] << " ";
    }
    cout << endl;

    // 4. Print eigenvectors
    cout << "\nEigenvector matrix V:\n";
    VA.print();

    // check of  VTAV==D, VDVT==A, VTV==1, VVT==1
    
    pp::matrix D(VA.size1(), VA.size2());

    for (int i = 0; i < wA.size(); i++) {
        D(i,i) = wA[i];
    }

    // Calculate

    std::cout << "Check of EVD, 1 means true" << "\n";

    auto VT = transpose(VA);
    auto left = VT * A * VA;
    std::cout << "VTAV == D: " << approx_equal(left, D) << "\n";

    auto right = VA * D * VT;
    std::cout << "VDVT == A: " << approx_equal(right, A) << "\n";

    auto I1 = VT * VA;
    pp::matrix I = identity_matrix(VA.size1()); // you need this
    std::cout << "VTV == I: " << approx_equal(I1, I) << "\n";

    auto I2 = VA * VT;
    std::cout << "VVT == I: " << approx_equal(I2, I) << "\n";

    // Assignment B (3 points)

    std::cout << "\n" << "Hydrogen atom s-wave radial Schrödinger equation on a grid" << "\n";

    std::ofstream out1("energy_vs_dr.dat");

    double rmax = 10.0;

    for (double dr = 0.05; dr <= 0.5; dr += 0.01) {
        double E0 = ground_state_energy(rmax, dr);
        out1 << dr << " " << E0 << "\n";
    }

    std::ofstream out2("energy_vs_rmax.dat");

    double dr = 0.1;

    for (double rmax = 2.0; rmax <= 20.0; rmax += 0.5) {
        double E0 = ground_state_energy(rmax, dr);
        out2 << rmax << " " << E0 << "\n";
    }

// Plotting different wavefunctions
    int npoints = (int)(rmax/dr) - 1;
    
    pp::vector r(npoints);
    for (int i = 0; i<npoints; i++) {
        r[i] = dr * (i + 1); // Skip r=0
    }

// Hamiltonian
    pp::matrix H(npoints, npoints);

    double coeff = -0.5 / (dr * dr);

    for (int i = 0; i < npoints - 1; i++) {
        H(i,i)     = -2 * coeff;
        H(i,i+1)   =  1 * coeff;
        H(i+1,i)   =  1 * coeff;
    }

// last diagonal element
    H(npoints-1, npoints-1) = -2 * coeff;

    for (int i = 0; i < npoints; i++) {
        H(i,i) += -1.0 / r[i];
    }

// Diagonalize 
    auto [eH, VH] = jacobi(H);    

//Finding eigenvalue

    std::cout << "Finding groundstate eigenvalue (expected -0.5)" << "\n";

    double E0 = eH[0];
    std::cout << "Ground state energy: " << E0 << "\n";

// Wavefunction

    double norm = 1.0 / sqrt(dr);

    pp::vector f0(npoints); // Ground state

    for (int i = 0; i < npoints; i++) {
        f0[i] = norm * VH(i,0);
    }

    pp::vector f1(npoints); // First excited state

    for (int i = 0; i < npoints; i++) {
        f1[i] = norm * VH(i,1);
    }

    pp::vector f2(npoints); // Second excited state

    for (int i = 0; i < npoints; i++) {
        f2[i] = norm * VH(i,2);
    }

// Output for plotting

    std::ofstream waveout("wavefunction.dat");

    waveout << "# r f0 f1 f2 \n";

    for (int i = 0; i < npoints; i++) {
        waveout << r[i] << " " 
            << f0[i] << " " 
            << f1[i] << " " 
            << f2[i] << "\n";
    }

// Timing

    std::ofstream timeout("timing.dat");

    for (int n = 50; n <= 500; n += 50) {

        pp::matrix A = random_symmetric_matrix(n);

        auto start = std::chrono::high_resolution_clock::now();
        auto [e, V] = jacobi(A);
        auto stop = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed = stop - start;
        std::cout << "n = "
                << n
                << " time = "
                << elapsed.count()
                << " seconds\n";
        timeout << n << " " << elapsed.count() << "\n";
    }

    return 0;
}