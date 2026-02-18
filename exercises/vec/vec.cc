// #include<iostream>
// #include<string>
// #include"vec.h"
// #include<cmath>


// namespace pp{
// 	// print for debugging
// 	void vec<T>::print(const std::string& s) const{
// 		std::cout << s << x << " " << y << " " << z << std::endl;
// 	}

// 	// overloading operator
// 	template<typename T>
// 	friend std::ostream& operator<< <T>(std::ostream& os, const vec<T>& v){
// 		os << "{ " << v.x << ", " << v.y << ", " << v.z << " } ";
// 		return os;
// 	}
// 	template<typename T>
// 	vec<T>& vec<T>::operator+=(const vec<T>& other){
// 		x+=other.x;
// 		y+=other.y;
// 		z+=other.z;
// 		return (*this); // (*this) ~ python's "self"
// 	}

// 	template<typename T>
// 	vec<T>& vec<T>::operator-=(const vec<T>& other){
// 		x-=other.x;
// 		y-=other.y;
// 		z-=other.z;
// 		return (*this); 
// 	}

// 	template<typename T>
// 	vec<T>& vec<T>::operator*=(T s){
// 		x*=s;
// 		y*=s;
// 		z*=s;
// 		return (*this); 
// 	}

// 	template<typename T>
// 	vec<T>& vec<T>::operator/=(T s){
// 		if(s == 0) throw std::runtime_error("division by zero");
// 		x/=s;
// 		y/=s;
// 		z/=s;
// 		return (*this); 
// 	}

// 	template<typename T>
// 	T vec<T>::dot(const vec<T>& other) const {
//     	return x * other.x + y * other.y + z * other.z;
// 	}

// 	template<typename T>
// 	vec<T> vec<T>::cross(const vec<T>& other) const {
//     	return vec(
// 			y * other.z - z * other.y,
// 			z * other.x - x * other.z,
// 			x * other.y - y * other.x
//     	);
// 	}

// 	template<typename T>
// 	T vec<T>::norm() const {
//     	return std::sqrt(x*x + y*y + z*z);
// 	}

// 	template<typename T>
// 	vec<T> operator+(vec<T> a, const vec<T>& b) {
// 		a += b;				// this is modern form, where the compiler makes a copy directly and 
// 		return a;			// returns it, instead of the programmer making one more copy, and 
// 							// returning that one
		
// 	}

// 	template<typename T>
// 	vec<T> operator-(vec<T> a, const vec<T>& b){
// 		a-=b;
// 		return a;
// 	}

// 	template<typename T>
// 	vec<T> operator-(const vec<T>& a) {
// 		return vec(-a.x, -a.y, -a.z);
// 	}

// 	template<typename T>
// 	vec<T> operator*(vec<T> a, T s) {
// 		return a *= s;
// 	}

// 	template<typename T>
// 	vec<T> operator*(T s, vec<T> a) {
// 		return a *= s;  
// 	}

// 	template<typename T>
// 	vec<T> operator/(vec<T> a, T s) {
// 		a /= s;
// 		return a;
// 	}

// 	// comparing Ts
// 	template<typename T>
// 	bool approx(T x, T y, T acc, T eps) {
// 		return (std::abs(x - y) <= acc) ||
// 			(std::abs(x - y) <= eps * std::max(std::abs(x), std::abs(y)));
// 	}

// 	// comparing vectors
// 	template<typename T>
// 	bool approx(const vec<T>& a, const vec<T>& b, T acc = 1e-6, T eps = 1e-6) {
// 		return approx(a.x, b.x, acc, eps) &&
// 			approx(a.y, b.y, acc, eps) &&
// 			approx(a.z, b.z, acc, eps);
// 	}

// }