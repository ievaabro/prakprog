#pragma once

#include <cassert>
#include <cstddef>
#include <iostream>

struct vector {
private:
    size_t n;
    double* data;

public:

    // constructor
    vector(size_t n)
        : n(n), data(new double[n]) {}

    // default constructor
    vector()
        : n(0), data(nullptr) {}

    // copy constructor
    vector(const vector& other)
        : n(other.n), data(new double[other.n]) {

        for(size_t i = 0; i < n; i++)
            data[i] = other.data[i];
    }

    // move constructor
    vector(vector&& other)
        : n(other.n), data(other.data) {

        other.n = 0;
        other.data = nullptr;
    }

    // destructor
    ~vector() {
        delete[] data;
    }

    // copy assignment
    vector& operator=(const vector& other) {

        if(this == &other) return *this;

        delete[] data;

        n = other.n;
        data = new double[n];

        for(size_t i = 0; i < n; i++)
            data[i] = other.data[i];

        return *this;
    }

    // move assignment
    vector& operator=(vector&& other) {

        if(this == &other) return *this;

        delete[] data;

        n = other.n;
        data = other.data;

        other.n = 0;
        other.data = nullptr;

        return *this;
    }

    // size
    size_t size() const {
        return n;
    }

    // indexing
    double& operator[](size_t i) {
        assert(i < n);
        return data[i];
    }

    const double& operator[](size_t i) const {
        assert(i < n);
        return data[i];
    }

    // print helper
    void print(const std::string& s = "") const {

        std::cout << s;

        for(size_t i = 0; i < n; i++)
            std::cout << data[i] << " ";

        std::cout << std::endl;
    }
};