#include <iostream>
#include <cmath>
#include <fstream>

#include "matrix.h"
#include "newton.h"
#include "ode.h"

// using namespace std;

std::vector<double> r_save;
std::vector<double> f_save;

pp::vector f1(pp::vector x){

    pp::vector y(1);

    y[0] = x[0]*x[0] - 2;

    return y;
}

pp::vector rosenbrock_grad(pp::vector x){

    double X = x[0];
    double Y = x[1];

    pp::vector g(2);

    g[0] =
        -2*(1-X)
        -400*X*(Y - X*X);

    g[1] =
        200*(Y - X*X);

    return g;
}

pp::vector himmel_grad(pp::vector x){

    double X = x[0];
    double Y = x[1];

    pp::vector g(2);

    g[0] =
        4*X*(X*X + Y - 11)
        + 2*(X + Y*Y - 7);

    g[1] =
        2*(X*X + Y - 11)
        + 4*Y*(X + Y*Y - 7);

    return g;
}

double M(double E)
{
    double rmin = 1e-4;
    double rmax = 8.0;

    pp::vector y(2);
    y[0] = rmin;
    y[1] = 1.0;

    auto ode = [E](double r, pp::vector y)
    {
        pp::vector dydr(2);
        dydr[0] = y[1];
        dydr[1] = -2.0 * (E + 1.0/r) * y[0];
        return dydr;
    };

    auto [rlist, ylist] = driver(ode, rmin, rmax, y, 0.01, 1e-4, 1e-4);

    // auto ylist = std::get<1>(result);

    r_save.clear();
    f_save.clear();

    for(std::size_t i = 0; i < rlist.size(); i++)
    {
        r_save.push_back(rlist[i]);
        f_save.push_back(ylist[i][0]);
    }

    pp::vector y_end = ylist.back();

    return y_end[0];
}

pp::vector M_wrapper(pp::vector Evec)
{
    pp::vector out(1);
    out[0] = M(Evec[0]);
    return out;
}

pp::vector schrodinger(double r, pp::vector y, double E)
{
    pp::vector dydr(2);

    dydr[0] = y[1];
    dydr[1] = -2.0 * (E + 1.0/r) * y[0];

    return dydr;
}

int main(){

    std::ofstream pout("roots.txt");

    //  sqrt(2) 

    pp::vector x1(1);

    x1[0] = 1;

    pp::vector r1 = newton(f1,x1);

    std::cout << "sqrt(2) test:\n";
    std::cout << r1[0] << "\n\n";

    pout << "sqrt(2) test:\n";
    pout << r1[0] << "\n\n";


    //  Rosenbrock 

    pp::vector xr(2);

    xr[0] = -1;
    xr[1] = 2;


    pp::vector rr = newton(rosenbrock_grad,xr);

    std::cout << "Rosenbrock minimum:\n";
    std::cout << rr[0] << " "
         << rr[1] << "\n\n";

    pout << "Rosenbrock minimum:\n";
    pout << rr[0] << " "
         << rr[1] << "\n\n";

    //  Himmelblau 

    pp::vector xh(2);

    xh[0] = 3;
    xh[1] = 1;

    pp::vector rh = newton(himmel_grad,xh);

    std::cout << "Himmelblau minimum:\n";
    std::cout << rh[0] << " "
         << rh[1] << "\n\n";

    pout << "Himmelblau minimum:\n";
    pout << rh[0] << " "
         << rh[1] << "\n\n";

    //  Schrödinger

    pp::vector E(1);
    E[0] = -0.5;   // vigtig start guess

    pp::vector root = newton(M_wrapper, E);

    std::cout << "Energy = " << root[0] << "\n";
    pout << "Energy = " << root[0] << "\n";

    std::ofstream file("wf.dat");

    for (std::size_t i = 0; i < r_save.size(); i++)    {
        file << r_save[i] << " " << f_save[i] << "\n";
    }

    return 0;
}