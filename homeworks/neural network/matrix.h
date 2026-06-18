#include<iostream>
#include<cstdio>
#include<cassert>
#include<iomanip>
#include<cmath>
#include<string>
#include<vector> // Storage container
#include<initializer_list>
#include<functional>
#include<ranges>

namespace pp{ // Using vectors - pp::vector v;

struct vector {
	std::vector<double> data; // The vector stores values in doubles

	vector() = default; // Empty vector
	vector(int n) : data(n) {} // Defines the size of the vector
	vector(std::initializer_list<double> list) : data(list) {} // Allows the construction of a vector like {1,2,3}
	vector(const vector&) = default; // copies the contructor
	vector(vector&&) noexcept = default; // Transfers the constructor into the right memory ownership

	vector& operator=(const vector&) = default; // Allows assignment v = w;
	vector& operator=(vector&&) noexcept = default;

//	auto n(){return std::views::iota(0,size());}
	void resize(int n) {data.resize(n);}
	inline int size() const {return data.size();} // sizes of vectors: v.size()
	inline double& operator[](int i) {return data[i];} // Index operator allows v[i] instead of v.data[i]
	inline const double& operator[](int i) const {return data[i];}

	vector& operator+=(const vector& other);
	vector& operator-=(const vector& other);
	vector& operator*=(double c);
	vector& operator/=(double c); // Implement v += w and v *= 2, from the .cc file
	double norm() const; // Vector length
	void print(std::string s="") const; // Prints the vector with an optional label
	vector map(std::function<double(double)> f) const; // Applies function to each element
}; //vector

vector operator+(vector a, const vector& b); // Allows different vector operations
vector operator-(vector a)                 ;
vector operator-(vector a, const vector& b);
vector operator*(vector a, const double c) ;
vector operator*(const double c, vector a) ;
vector operator/(vector a, const double c) ;
bool approx(double x, double y, double acc=1e-6, double eps=1e-6); // Approximations - compares element by element
bool approx(const vector& a,const vector& b,double acc=1e-6,double eps=1e-6);

struct matrix {
	std::vector<pp::vector> cols; // Matrix stored in columns
	matrix()=default; // Empty matrix
	matrix(int n,int m) : cols(m, pp::vector(n)) {} // Creates matrix with n rows and m columns
	matrix(const matrix& other)=default;
	matrix(matrix&& other)=default;
	matrix& operator=(const matrix& other)=default;
	matrix& operator=(matrix&& other)=default;
	inline double& operator()(int i, int j){return cols[j][i];} // access element (i, j)
	inline double& operator[](int i, int j){return cols[j][i];} // access elements in another way
	inline const double& operator()(int i, int j)const{return cols[j][i];}
	inline const double& operator[](int i, int j)const{return cols[j][i];}
	inline vector& operator[](int i){return cols[i];} // Returns column i
	inline const vector& operator[](int i) const {return cols[i];}
//	void resize(int n, int m);
	inline int size1() const {return cols[0].size();}  // Matrix size - number of rows
	inline int size2() const {return cols.size();} // number of columns
	void setid();
	matrix transpose() const; // Matrix transpose 
	matrix T() const {return transpose();} // shortcut A.T()
	matrix& operator+=(const matrix& B); // Implementations of matrix operations
	matrix& operator-=(const matrix& B);
	matrix& operator*=(const double c);
	matrix& operator/=(const double c);
	matrix& operator*=(const matrix&);
	matrix  operator^(int);
	void print(std::string s="") const; //Display matrix
}; //matrix

matrix operator+(matrix A, const matrix& B); // Free matrix operators (allow different syntax)
matrix operator-(matrix A, const matrix& B);
matrix operator*(const matrix& A, const matrix& B);
matrix operator*(matrix A, const double c);
matrix operator*(const double c, matrix A);
matrix operator/(matrix A, const double c);
vector operator*(const matrix& A, const vector& v);


inline std::ostream& operator<<(std::ostream& os, const vector& v){

    os << "(";

    for(int i = 0; i < v.size(); i++){

        os << v[i];

        if(i < v.size()-1)
            os << ", ";
    }

    os << ")";

    return os;
}

}//pp