#include "vector.h"

vector::vector(int size)
    : n(size), data(new double[size])
{
    for(int i=0;i<n;i++)
        data[i]=0;
}

vector::vector()
    : n(0), data(nullptr)
{}

vector::vector(const vector& v)
    : n(v.n), data(new double[v.n])
{
    for(int i=0;i<n;i++)
        data[i]=v.data[i];
}

vector::vector(vector&& v)
    : n(v.n), data(v.data)
{
    v.n=0;
    v.data=nullptr;
}

vector::~vector(){
    delete[] data;
}

vector& vector::operator=(const vector& v){

    if(this==&v) return *this;

    delete[] data;

    n=v.n;
    data=new double[n];

    for(int i=0;i<n;i++)
        data[i]=v.data[i];

    return *this;
}

vector& vector::operator=(vector&& v){

    delete[] data;

    n=v.n;
    data=v.data;

    v.n=0;
    v.data=nullptr;

    return *this;
}

double& vector::operator[](int i){
    assert(i>=0 && i<n);
    return data[i];
}

const double& vector::operator[](int i) const{
    assert(i>=0 && i<n);
    return data[i];
}

int vector::size() const{
    return n;
}

void vector::print(const std::string& s) const{

    std::cout << s;

    for(int i=0;i<n;i++)
        std::cout << data[i] << " ";

    std::cout << "\n";
}