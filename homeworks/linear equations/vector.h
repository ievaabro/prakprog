#ifndef PP_VECTOR_H
#define PP_VECTOR_H

#include <vector>
#include <string>
#include <iostream>

namespace pp {

class vector {
public:
    std::vector<double> data;

    vector(int n);

    int size() const;

    double& operator[](int i);
    const double& operator[](int i) const;   

    void print(const std::string& s = "") const;

    vector& operator+=(const vector& other);
    vector& operator-=(const vector& other);
    vector& operator*=(double s);
    vector& operator/=(double s);

    double dot(const vector& other) const;
    double norm() const;
};

// free operators
std::ostream& operator<<(std::ostream& os, const vector& v);

vector operator+(vector a, const vector& b);
vector operator-(vector a, const vector& b);
vector operator-(const vector& a);
vector operator*(vector a, double s);
vector operator*(double s, vector a);
vector operator/(vector a, double s);

// approx
bool approx(double x, double y, double acc=1e-9, double eps=1e-9);
bool approx(const vector& a, const vector& b, double acc=1e-9, double eps=1e-9);

} // namespace pp

#endif