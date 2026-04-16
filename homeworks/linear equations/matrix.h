#pragma once
#include <vector>
#include "vector.h"

namespace pp {

struct matrix {
    std::vector<vector> cols;

    matrix();
    matrix(int n, int m);
    matrix(const matrix&);
    matrix(matrix&&);

    matrix& operator=(const matrix&);
    matrix& operator=(matrix&&);

    int size1() const;
    int size2() const;

    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    vector& operator[](int j);
    const vector& operator[](int j) const;

    void setid();
    matrix transpose() const;

    matrix& operator+=(const matrix& B);
    matrix& operator-=(const matrix& B);
    matrix& operator*=(double c);
    matrix& operator/=(double c);

    void print(std::string s="") const;
};

matrix operator+(matrix A, const matrix& B);
matrix operator-(matrix A, const matrix& B);
matrix operator*(const matrix& A, const matrix& B);
matrix operator*(matrix A, double c);
matrix operator*(double c, matrix A);
matrix operator/(matrix A, double c);
vector operator*(const matrix& A, const vector& v);

}