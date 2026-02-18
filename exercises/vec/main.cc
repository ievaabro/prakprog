#include<iostream>
#include<vector>
#include"vec.h"

using namespace pp;

int main(){
	vec<double> v1{1.0, 2.0, 3.0};
    vec<double> v2{4.0, 5.0, 6.0};
    vec<double> v3;

    std::cout << "v1: " << v1 << "\n";
    std::cout << "v2: " << v2 << "\n";


	// plus
    v3 = v1 + v2;
    std::cout << "v1 + v2 = " << v3 << "\n";

    // minus
    v3 = v2 - v1;
    std::cout << "v2 - v1 = " << v3 << "\n";

    // unary minus
    v3 = -v1;
    std::cout << "-v1 = " << v3 << "\n";

    // multiplication
    v3 = v1 * 2.0;
    std::cout << "v1 * 2 = " << v3 << "\n";
    v3 = 0.5 * v2;
    std::cout << "0.5 * v2 = " << v3 << "\n";

    // division
    v3 = v2 / 2.0;
    std::cout << "v2 / 2 = " << v3 << "\n";


	vec v4{1.0, 1.0, 1.0};
    v4 += v1;
    std::cout << "v4 += v1 -> " << v4 << "\n";
    v4 -= v2;
    std::cout << "v4 -= v2 -> " << v4 << "\n";
    v4 *= 3.0;
    std::cout << "v4 *= 3 -> " << v4 << "\n";
    v4 /= 3.0;
    std::cout << "v4 /= 3 -> " << v4 << "\n";
	

	std::cout << "v1 dot v2 = " << v1.dot(v2) << "\n";

    vec v5 = v1.cross(v2);
    std::cout << "v1 cross v2 = " << v5 << "\n";

    std::cout << "norm of v1 = " << v1.norm() << "\n";

	
	vec v6{1.000001, 2.0, 3.0};
		if (approx(v1, v6)) {
			std::cout << "v1 approximately equals v6\n";
		} else {
			std::cout << "v1 NOT approximately equal to v6\n";
	}


	v1.print("v1 = ");
    v2.print("v2 = ");

	return 0;
}