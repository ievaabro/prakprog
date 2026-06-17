#include <iostream>
#include <random>
#include <string>
#include <cstdlib>
#include <fstream>
#include <chrono>

#include "matrix.h"
#include "EVD.h"
#include <tuple>

namespace pp{
    using pp::vector;
    using pp::matrix;

std::tuple<vector,matrix> jacobi(matrix A){// "A" is a copy
	int n=A.size1();
	matrix V(n,n); V.setid(); vector w(n);
	/* run Jacobi rotations on A and update V */
	/* copy diagonal elements into w */

    bool changed;

    do{
        changed = false;

        for(int p = 0; p < n-1; p++){
            for(int q = p+1; q < n; q++){

                double apq = A(p,q);
                double app = A(p,p);
                double aqq = A(q,q);

                double theta = 0.5 * std::atan2(2*apq, aqq - app);

                double c = std::cos(theta);
                double s = std::sin(theta);

                double new_app = c*c*app - 2*s*c*apq + s*s*aqq;
                double new_aqq = s*s*app + 2*s*c*apq + c*c*aqq;

                if(new_app != app || new_aqq != aqq){
                    changed = true;

                    timesJ(A, p, q,  theta);   // A ← A*J
                    Jtimes(A, p, q, -theta);   // A ← Jᵀ*A
                    timesJ(V, p, q,  theta);   // V ← V*J
                }
            }
        }
    } while(changed);

    for(int i = 0; i < n; i++){
        w[i] = A(i,i);
    }

	return std::make_tuple(w,V);
	}//jacobi

void timesJ(matrix& A, int p, int q, double theta){
    double c = std::cos(theta), s = std::sin(theta);
    for(int i = 0; i < A.size1(); i++){
        double aip = A(i,p), aiq = A(i,q);
        A(i,p) = c*aip - s*aiq;
        A(i,q) = s*aip + c*aiq;
    }
}
void Jtimes(matrix& A, int p, int q, double theta){    
    double c = std::cos(theta), s = std::sin(theta);
    for(int j = 0; j < A.size2(); j++){
        double apj = A(p,j), aqj = A(q,j);
        A(p,j) =  c*apj + s*aqj;
        A(q,j) = -s*apj + c*aqj;
    }
}

}//EVD