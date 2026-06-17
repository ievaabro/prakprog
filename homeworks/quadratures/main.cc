#include <iostream>
#include <cmath>
#include <functional>
#include <vector>
#include <fstream>
#include <string>

#include "ROQAI.h"

using namespace std;

int ncalls = 0;

auto f2_count = [](double x){
    ++ncalls;
    return 1/std::sqrt(x);
};

auto f4_count = [](double x){
    ++ncalls;
    return std::log(x)/std::sqrt(x);
};

auto f_exp_count = [](double x){
    ++ncalls;
    return std::exp(-x);
};

auto f_gauss_count = [](double x){
    ++ncalls;
    return std::exp(-x*x);
};

double call_counter(function<double(double)> f, double x){
    ncalls++;
    return f(x);
}

double erf_integral(double z, double acc){

    if(z < 0)
        return -erf_integral(-z, acc);

    if(z <= 1){
        auto f = [](double x){
            return std::exp(-x*x);
        };
        return 2/std::sqrt(M_PI) * integrate(f, 0, z, acc, 0);
    }
    else{
        auto f = [z](double t){
            double x = z + (1 - t)/t;
            return std::exp(-x*x)/(t*t);
        };
        return 1 - 2/std::sqrt(M_PI) * integrate(f, 0, 1, acc, 0);
    }
}

int main(){

    struct Test {
        function<double(double)> f;
        double a,b;
        double exact;
        string name;
    };

    vector<Test> tests = {

        {
            [](double x){ return sqrt(x); },
            0,1,
            2.0/3.0,
            "∫₀¹ sqrt(x) dx"
        },

        {
            [](double x){ return 1.0/sqrt(x); },
            0,1,
            2.0,
            "∫₀¹ 1/sqrt(x) dx"
        },

        {
            [](double x){ return sqrt(1-x*x); },
            0,1,
            M_PI/4.0,
            "∫₀¹ sqrt(1-x²) dx"
        },

        {
            [](double x){ return log(x)/sqrt(x); },
            0,1,
            -4.0,
            "∫₀¹ ln(x)/sqrt(x) dx"
        }
    };

    ofstream txt_file("initial_integral_solutions.txt");

    for(const auto& test : tests){

        ncalls = 0;

        auto counted_f = [test](double x){
            return call_counter(test.f,x);
        };

        double result = integrate(counted_f,test.a,test.b);

        double error = fabs(result - test.exact);

        txt_file << "-----------------------------------\n";
        txt_file << test.name << "\n";
        txt_file << "Result        = " << result << "\n";
        txt_file << "Exact         = " << test.exact << "\n";
        txt_file << "Actual error  = " << error << "\n";
        txt_file << "Function calls= " << ncalls << "\n";
    }
    txt_file.close();

    ofstream file("erf_data.dat");

    for(double z = -3.0; z <= 3.0; z += 0.05){
        double val = erf_integral(z, 1e-6);
        double ref = erf(z); // or std::erf(z)

        file << z << " " << val << " " << ref
            << " " << fabs(ref - val) << "\n";
    }

    file.close();

    double exact = 0.8427007929497148;
    std::cout << "erf(1) ≈ " << erf_integral(1, 1e-6)
              << " (exact " << exact << ")\n";

    std::ofstream out("erf_convergence.dat");

    for(double acc = 1e-1; acc >= 1e-8; acc *= 0.1){
        double val = erf_integral(1.0, acc);
        double err = std::abs(val - exact);

        out << acc << " " << err << "\n";
    }

    out.close();

    std::ofstream fout("Variable_transformation_quadratures.txt");
    // Assignment 2
    ncalls = 0;
    double I2 = integrate(f2_count,0,1);
    int calls_normal = ncalls;

    ncalls = 0;
    double I2_CC = integrate_cc(f2_count,0,1);
    int calls_cc = ncalls;

    fout << "\nIntegral 1/sqrt(x):\n";
    fout << "  normal = " << I2 << ", calls = " << calls_normal << "\n";
    fout << "  CC     = " << I2_CC << ", calls = " << calls_cc << "\n";

    ncalls = 0;
    double I4 = integrate(f4_count,0,1);
    calls_normal = ncalls;

    ncalls = 0;
    double I4_CC = integrate_cc(f4_count,0,1);
    calls_cc = ncalls;

    fout << "\nIntegral log(x)/sqrt(x):\n";
    fout << "  normal = " << I4 << ", calls = " << calls_normal << "\n";
    fout << "  CC     = " << I4_CC << ", calls = " << calls_cc << "\n";

    fout << "\nInfinite interval tests:\n";

    // exp(-x)
    ncalls = 0;
    double Iexp = integrate_inf(f_exp_count, 0,
        std::numeric_limits<double>::infinity(), 1e-6, 1e-6);

    int calls_exp = ncalls;

    fout << "exp(-x) from 0 to ∞ = " << Iexp
            << " (exact 1), calls = " << calls_exp << "\n";

    // Gaussian
    ncalls = 0;
    double Igauss = integrate_inf(f_gauss_count,
        -std::numeric_limits<double>::infinity(),
        std::numeric_limits<double>::infinity(), 1e-6, 1e-6);

    int calls_gauss = ncalls;

    fout << "exp(-x^2) from -∞ to ∞ = " << Igauss
            << " (exact " << std::sqrt(M_PI)
            << "), calls = " << calls_gauss << "\n";
    
    fout.close();

    return 0;
}