#include<iostream>
#include<string>
#include"vec.h"
#include<cmath>

namespace pp{
	// print for debugging
	void vec::print(const std::string& s) const{
		std::cout << s << x << " " << y << " " << z << std::endl;
	}

	// overloading operator
	std::ostream& operator<<(std::ostream& os, const vec& v){
		os << "{ " << v.x << ", " << v.y << ", " << v.z << " } ";
		return os;
	}

	vec& vec::operator+=(const vec& other){
		x+=other.x;
		y+=other.y;
		z+=other.z;
		return (*this); // (*this) ~ python's "self"
	}

	vec& vec::operator-=(const vec& other){
		x-=other.x;
		y-=other.y;
		z-=other.z;
		return (*this); 
	}

	vec& vec::operator*=(double s){
		x*=s;
		y*=s;
		z*=s;
		return (*this); 
	}

	vec& vec::operator/=(double s){
		if(s == 0) throw std::runtime_error("division by zero");
		x/=s;
		y/=s;
		z/=s;
		return (*this); 
	}

	double vec::dot(const vec& other) const {
    	return x * other.x + y * other.y + z * other.z;
	}

	vec vec::cross(const vec& other) const {
    	return vec(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
    	);
	}

	double vec::norm() const {
    	return std::sqrt(x*x + y*y + z*z);
	}

	vec operator+(vec a, const vec& b) {
		a += b;				// this is modern form, where the compiler makes a copy directly and 
		return a;			// returns it, instead of the programmer making one more copy, and 
							// returning that one
		
	}

	vec operator-(vec a, const vec& b){
		a-=b;
		return a;
	}

	vec operator-(const vec& a) {
		return vec(-a.x, -a.y, -a.z);
	}

	vec operator*(vec a, double s) {
		return a *= s;
	}

	vec operator*(double s, vec a) {
		return a *= s;  
	}

	vec operator/(vec a, double s) {
		a /= s;
		return a;
	}

	// comparing doubles
	bool approx(double x, double y, double acc, double eps) {
		return (std::abs(x - y) <= acc) ||
			(std::abs(x - y) <= eps * std::max(std::abs(x), std::abs(y)));
	}

	// comparing vectors
	bool approx(const vec& a, const vec& b, double acc, double eps) {
		return approx(a.x, b.x, acc, eps) &&
			approx(a.y, b.y, acc, eps) &&
			approx(a.z, b.z, acc, eps);
	}

}