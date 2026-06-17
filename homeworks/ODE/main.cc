#include <iostream>
#include <fstream>
#include <cmath>

#include "ode.h"

vector f(double x, vector y){ // Example
    (void)x;

    vector dydx(2);

    dydx[0] = y[1];     // u' = v
    dydx[1] = -y[0];    // v' = -u

    return dydx;
}

vector pend(double t, vector y1){ // Pendulum assignment
    (void)t;
    double b = 0.25;
    double c = 5.0;
    vector dydt(2);

    double theta = y1[0];
    double omega = y1[1];

    dydt[0] = omega;
    dydt[1] = -b*omega - c*std::sin(theta);

    return dydt;
}


std::function<vector(double, vector)> orbit(double eps){
    return [=](double /*phi*/, vector y){
        vector dydx(2);
        dydx[0] = y[1];
        dydx[1] = 1 - y[0] + eps*y[0]*y[0];
        return dydx;
    };
}

int main(){

    vector y0(2);
    y0[0] = 1;
    y0[1] = 0;

    auto [xs,ys] = driver(
        f,
        0,
        20,
        y0,
        0.1,
        1e-3,
        1e-3
    );

    std::ofstream out("out.data");

    for(size_t i=0;i<xs.size();i++){
        out << xs[i] << " "
            << ys[i][0] << " "
            << cos(xs[i]) << "\n";
    }

    // Pendulum assignment
    vector y10(2);
    y10[0] = M_PI - 0.1;
    y10[1] = 0.0;

    auto [ts, ys1] = driver(
        pend,
        0.0,
        10.0,
        y10,
        0.1,
        1e-4,
        1e-4
    );

    std::ofstream pendout("pendulum.data");

    for(size_t i=0;i<ts.size();i++){
        pendout << ts[i] << " "
                << ys1[i][0] << " "   // theta
                << ys1[i][1] << "\n"; // omega
    }

    // Orbit data
    std::cout << "START orbit section\n";
    std::ofstream orbitfile("orbit.data");
    std::cout << "OPENED orbit file\n";

    std::vector<double> epss    = {0.0, 0.0, 0.01};
    std::vector<double> uprimes = {0.0, -0.5, -0.5};

    for (size_t i = 0; i < epss.size(); i++){
        auto F = orbit(epss[i]);
        vector init(2);
        init[0] = 1.0;
        init[1] = uprimes[i];
        auto [phi, y2] = driver(F, 0.0, 8*M_PI, init, 0.01, 1e-5, 1e-5);

        orbitfile << "# eps=" << epss[i]
                  << " u'(0)=" << uprimes[i] << "\n";

        for (size_t j = 0; j < phi.size(); j++)
            orbitfile << phi[j] << " " << y2[j][0] << "\n";

        orbitfile << "\n\n";
    }

    return 0;
}