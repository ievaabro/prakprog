// #pragma once
#include <iostream>
#include <string>
#include<string>
// #include"vec.h"
#include<cmath>

namespace pp{
    template<typename T>
    struct vec {
        T x, y, z;

        // constructors
        vec(T x, T y, T z) : x(x), y(y), z(z) {}  // parameterized
        vec() : vec(0, 0, 0) {}                                    // default
        vec(const vec<T>&) = default;                                 // copy
        vec(vec<T>&&) = default;                                      // move
        ~vec() = default;                                          // destructor

        // assignment
        vec<T>& operator=(const vec<T>&) = default;                     // copy assignment
        vec<T>& operator=(vec<T>&&) = default;                          // move assignment

        // arithmetic
        vec<T>& operator+=(const vec<T>&);
        vec<T>& operator-=(const vec<T>&);
        vec<T>& operator*=(T);
        vec<T>& operator/=(T);

        // utility
        void set(T a, T b, T c) { x = a; y = b; z = c; }
        void print(const std::string& s = "") const;              // for debugging

        // stream output
        friend std::ostream& operator<< <T>(std::ostream&, const vec<T>&);

        T dot(const vec<T>& other) const;
        vec<T> cross(const vec<T>& other) const;
        T norm() const;    
    };

    // non-member operators
    template<typename T>
    vec<T> operator+(vec<T> a, const vec<T>& b);
    template<typename T>
    vec<T> operator-(vec<T> a, const vec<T>& b);
    template<typename T>
    vec<T> operator-(const vec<T>& a);        // unary minus stays const&, not modern?
    template<typename T>
    vec<T> operator*(vec<T> a, T s);
    template<typename T>
    vec<T> operator*(T s, vec<T> a);
    template<typename T>
    vec<T> operator/(vec<T> a, T s);



    // approximate equality
    template<typename T>
    bool approx(T x, T y, T acc = 1e-6, T eps = 1e-6);
    template<typename T>
    bool approx(const vec<T>& a, const vec<T>& b, T acc = 1e-6, T eps = 1e-6);
}





















namespace pp{
    template<typename T>
	// print for debugging
	void vec<T>::print(const std::string& s) const{
		std::cout << s << x << " " << y << " " << z << std::endl;
	}

	// overloading operator
	template<typename T>
	std::ostream& operator<< (std::ostream& os, const vec<T>& v){
		os << "{ " << v.x << ", " << v.y << ", " << v.z << " } ";
		return os;
	}
	template<typename T>
	vec<T>& vec<T>::operator+=(const vec<T>& other){
		x+=other.x;
		y+=other.y;
		z+=other.z;
		return (*this); // (*this) ~ python's "self"
	}

	template<typename T>
	vec<T>& vec<T>::operator-=(const vec<T>& other){
		x-=other.x;
		y-=other.y;
		z-=other.z;
		return (*this); 
	}

	template<typename T>
	vec<T>& vec<T>::operator*=(T s){
		x*=s;
		y*=s;
		z*=s;
		return (*this); 
	}

	template<typename T>
	vec<T>& vec<T>::operator/=(T s){
		if(s == 0) throw std::runtime_error("division by zero");
		x/=s;
		y/=s;
		z/=s;
		return (*this); 
	}

	template<typename T>
	T vec<T>::dot(const vec<T>& other) const {
    	return x * other.x + y * other.y + z * other.z;
	}

	template<typename T>
	vec<T> vec<T>::cross(const vec<T>& other) const {
    	return vec(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
    	);
	}

	template<typename T>
	T vec<T>::norm() const {
    	return std::sqrt(x*x + y*y + z*z);
	}

	template<typename T>
	vec<T> operator+(vec<T> a, const vec<T>& b) {
		a += b;				// this is modern form, where the compiler makes a copy directly and 
		return a;			// returns it, instead of the programmer making one more copy, and 
							// returning that one
		
	}

	template<typename T>
	vec<T> operator-(vec<T> a, const vec<T>& b){
		a-=b;
		return a;
	}

	template<typename T>
	vec<T> operator-(const vec<T>& a) {
		return vec(-a.x, -a.y, -a.z);
	}

	template<typename T>
	vec<T> operator*(vec<T> a, T s) {
		return a *= s;
	}

	template<typename T>
	vec<T> operator*(T s, vec<T> a) {
		return a *= s;  
	}

	template<typename T>
	vec<T> operator/(vec<T> a, T s) {
		a /= s;
		return a;
	}

	// comparing Ts
	template<typename T>
	bool approx(T x, T y, T acc, T eps) {
		return (std::abs(x - y) <= acc) ||
			(std::abs(x - y) <= eps * std::max(std::abs(x), std::abs(y)));
	}

	// comparing vectors
	template<typename T>
	bool approx(const vec<T>& a, const vec<T>& b, T acc, T eps) {
		return approx(a.x, b.x, acc, eps) &&
			approx(a.y, b.y, acc, eps) &&
			approx(a.z, b.z, acc, eps);
	}

}