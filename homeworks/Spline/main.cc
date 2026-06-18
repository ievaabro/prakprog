#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include "vec.h"
#include "quadspline.h"

// Deklarationer fra Ispline.cc
double linterp(const vector& x, const vector& y, double z);
double linterpInteg(const vector& x, const vector& y, double z);

int main() {
    // Opret tabel: x = 0, 0.5, 1, ..., 9 og y = cos(x)
    int n = 19;  // 0 til 9 med step 0.5
    vector x(n), y(n);
    
    for (int i = 0; i < n; i++) {
        x[i] = i * 0.5;
        y[i] = cos(x[i]);
    }
    
    // Generer data til plots
    FILE* interp_file = fopen("interp.data", "w");
    FILE* integ_file = fopen("integ.data", "w");
    
    int npoints = 200;
    for (int i = 0; i < npoints; i++) {
        double z = x[0] + (x[n-1] - x[0]) * i / (npoints - 1);
        
        double y_interp = linterp(x, y, z);
        double y_exact = cos(z);
        
        double integ_interp = linterpInteg(x, y, z);
        double integ_exact = sin(z) - sin(x[0]);  // ∫cos(t)dt = sin(t)
        
        fprintf(interp_file, "%g %g %g\n", z, y_interp, y_exact);
        fprintf(integ_file, "%g %g %g\n", z, integ_interp, integ_exact);
    }
    
    fclose(interp_file);
    fclose(integ_file);
    
    // Udskriv også tabelpunkterne
    FILE* points_file = fopen("points.data", "w");
    for (int i = 0; i < n; i++) {
        fprintf(points_file, "%g %g\n", x[i], y[i]);
    }
    fclose(points_file);
    
    printf("Data saved in interp.data, integ.data and points.data\n");
    
    int n1 = 5;
    vector x1(n1), y1(n1);

    for(int i = 0; i < n1; i++) {
        x1[i] = i + 1;
        y1[i] = 1.0;
    }

    auto f = make_qspline(x1, y1);

    std::ofstream file("Out.txt");

    file << "Flat function, should only be 1's" << "\n";

    for(double z1 = 1; z1 <= 5; z1 += 0.5) {
        file << z1 << " " << f(z1) << "\n";
    }

    for(int i = 0; i < n1; i++) {
    x1[i] = i + 1;
    y1[i] = x1[i];
    }
    
    auto f1 = make_qspline(x1, y1);

    file << "Linear function" << "\n";
    for(double z = 1; z <= 5; z += 0.5) {
        file << z << " " << f1(z) << "\n";
    }
    double a = f1(2.0);

    x1[0] = 999;  
    y1[0] = 999;

    file << "Test of moving the function, should be the same as before:" << "\n";
    for(double z = 1; z <= 5; z += 0.5) {
        file << z << " " << f1(z) << "\n";
    }

    double b = f1(2.0);

    file << "testing of move with a certain value: Before move f(2.0) = " << a << " After move f(2.0) = " << b << "\n";

    return 0;
}