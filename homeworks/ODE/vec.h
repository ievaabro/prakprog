#pragma once
#include <vector>
#include <cmath>
#include <initializer_list>

class vector {
private:
    std::vector<double> data;

public:
    vector(std::initializer_list<double> list);
    vector(int n);

    vector& operator+=(const vector& other);

    double& operator[](int i);
    double operator[](int i) const;

    int size() const;
    double norm() const;
};

vector operator+(const vector& a, const vector& b);
vector operator-(const vector& a, const vector& b);
vector operator*(const vector& v, double c);
vector operator*(double c, const vector& v);
vector operator/(const vector& v, double c);