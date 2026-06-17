#include "vec.h"

/* constructor */

vector::vector(int n){
    data.resize(n);
}

int vector::size() const{
    return data.size();
}

vector::vector(std::initializer_list<double> list){
    data = std::vector<double>(list);
}

double& vector::operator[](int i){
    return data[i];
}

double vector::operator[](int i) const{
    return data[i];
}

/* norm */

double vector::norm() const{
    double sum = 0;

    for(int i=0;i<size();i++)
        sum += data[i]*data[i];

    return std::sqrt(sum);
}

/* addition */

vector operator+(const vector& a, const vector& b){

    vector c(a.size());

    for(int i=0;i<a.size();i++)
        c[i] = a[i] + b[i];

    return c;
}

/* subtraction */

vector operator-(const vector& a, const vector& b){

    vector c(a.size());

    for(int i=0;i<a.size();i++)
        c[i] = a[i] - b[i];

    return c;
}

/* scalar multiplication */

vector operator*(const vector& v, double c){

    vector r(v.size());

    for(int i=0;i<v.size();i++)
        r[i] = v[i]*c;

    return r;
}

vector operator*(double c, const vector& v){
    return v*c;
}

/* scalar division */

vector operator/(const vector& v, double c){

    vector r(v.size());

    for(int i=0;i<v.size();i++)
        r[i] = v[i]/c;

    return r;
}

vector& vector::operator+=(const vector& other){
    for(size_t i=0;i< data.size();i++){
        (*this)[i] += other[i];
    }
    return *this;
}