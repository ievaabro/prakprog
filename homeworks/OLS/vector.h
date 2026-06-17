#pragma once
#include <iostream>
#include <cassert>

class vector {
private:
    int n;
    double* data;

public:

    // constructors
    vector(int size);
    vector();

    vector(const vector&);
    vector(vector&&);

    ~vector();

    // assignment
    vector& operator=(const vector&);
    vector& operator=(vector&&);

    // access
    double& operator[](int i);
    const double& operator[](int i) const;

    int size() const;

    void print(const std::string& s="") const;
};