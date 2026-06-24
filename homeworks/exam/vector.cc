#include <iostream>
#include <cmath>
#include <stdexcept>
#include "vector.h"

#define SELF (*this)

namespace pp {

//constructor
vector::vector(int n) : data(n, 0.0) {}


int vector::size() const {
    return data.size();
}


//indexing 
// non-const access
double& vector::operator[](int i) {
    return data[i];
}

// const access
const double& vector::operator[](int i) const {
    return data[i];
}


void vector::print(const std::string& s) const {
    std::cout << s;
    for (int i = 0; i < size(); i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;
}


//stream output
std::ostream& operator<<(std::ostream& os, const vector& v) {
    os << "{ ";
    for (int i = 0; i < v.size(); i++)
        os << v[i] << " ";
    os << "}";
    return os;
}


//operators 
vector& vector::operator+=(const vector& other) {
    for (int i = 0; i < size(); i++)
        data[i] += other[i];
    return SELF;
}

vector& vector::operator-=(const vector& other) {
    for (int i = 0; i < size(); i++)
        data[i] -= other[i];
    return SELF;
}

vector& vector::operator*=(double s) {
    for (int i = 0; i < size(); i++)
        data[i] *= s;
    return SELF;
}

vector& vector::operator/=(double s) {
    if (s == 0)
        throw std::runtime_error("division by zero");

    for (int i = 0; i < size(); i++)
        data[i] /= s;

    return SELF;
}


double vector::dot(const vector& other) const {
    double sum = 0.0;
    for (int i = 0; i < size(); i++)
        sum += data[i] * other[i];
    return sum;
}

double vector::norm() const {
    return std::sqrt(dot(*this));
}


vector operator+(vector a, const vector& b) {
    a += b;
    return a;
}

vector operator-(vector a, const vector& b) {
    a -= b;
    return a;
}

vector operator-(const vector& a) {
    vector r(a.size());
    for (int i = 0; i < a.size(); i++)
        r[i] = -a[i];
    return r;
}

vector operator*(vector a, double s) {
    return a *= s;
}

vector operator*(double s, vector a) {
    return a *= s;
}

vector operator/(vector a, double s) {
    return a /= s;
}


bool approx(double x, double y, double acc, double eps) {
    return (std::abs(x - y) <= acc) ||
           (std::abs(x - y) <= eps * std::max(std::abs(x), std::abs(y)));
}

bool approx(const vector& a, const vector& b, double acc, double eps) {
    if (a.size() != b.size())
        return false;

    for (int i = 0; i < a.size(); i++)
        if (!approx(a[i], b[i], acc, eps))
            return false;

    return true;
}

} // for namespace pp