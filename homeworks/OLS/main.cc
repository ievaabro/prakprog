#include <iostream>
#include <cmath>
#include <fstream>
#include "lsfit.h"

int main(){

    pp::vector t(9);
    pp::vector y(9);
    pp::vector dy(9);

    t[0]=1;   y[0]=117;   dy[0]=6;
    t[1]=2;   y[1]=100;   dy[1]=5;
    t[2]=3;   y[2]=88;    dy[2]=4;
    t[3]=4;   y[3]=72;    dy[3]=4;
    t[4]=6;   y[4]=53;    dy[4]=4;
    t[5]=9;   y[5]=29.5;  dy[5]=3;
    t[6]=10;  y[6]=25.2;  dy[6]=3;
    t[7]=13;  y[7]=15.2;  dy[7]=2;
    t[8]=15;  y[8]=11.1;  dy[8]=2;

    pp::vector Y(9);
    pp::vector dY(9);

    for(int i=0;i<9;i++){
        Y[i]  = log(y[i]);
        dY[i] = dy[i]/y[i];
    }

    auto fs = std::vector<std::function<double(double)>>{
        [](double){ return 1.0; },
        [](double x){ return x; }
    };

    // pp::vector c = lsfit(fs,t,Y,dY);
    auto [c,Cov] = lsfit(fs,t,Y,dY);


    double c0 = c[0];
    double c1 = -c[1];

    double dc0 = std::sqrt(Cov(0,0));
    double dc1 = std::sqrt(Cov(1,1));

    double a = exp(c0);

    double T12  = log(2.0)/c1;

    double dT12 =
        log(2.0)/(c1*c1)*dc1;


    std::ofstream pout("Out.txt");

    pout << "a = " << a << "\n";
    pout << "lambda = " << c1 << "+/-" << dc1 << "\n";
    pout << "Half-life = " << T12 << "+/-" << dT12 << " days\n";
    pout << "Modern Value = 3.6316 days\n";

    std::ofstream datafile("data.txt");

    for(int i=0;i<9;i++){
        datafile
            << t[i]  << " "
            << y[i]  << " "
            << dy[i] << "\n";
    }
    
    std::ofstream fitout("fit.dat");

    for(double tt=0; tt<=15; tt+=0.1){

        // best fit
        double yfit = a * exp(-c1 * tt);

        // combinations
        double a_pp = exp(c0 + dc0);
        double a_pm = exp(c0 + dc0);
        double a_mp = exp(c0 - dc0);
        double a_mm = exp(c0 - dc0);

        double lambda_pp = (c1 + dc1);
        double lambda_pm = (c1 - dc1);
        double lambda_mp = (c1 + dc1);
        double lambda_mm = (c1 - dc1);

        double y_pp = a_pp * exp(-lambda_pp * tt);
        double y_pm = a_pm * exp(-lambda_pm * tt);
        double y_mp = a_mp * exp(-lambda_mp * tt);
        double y_mm = a_mm * exp(-lambda_mm * tt);

        // envelope (min/max)
        double y_max = std::max({y_pp, y_pm, y_mp, y_mm});
        double y_min = std::min({y_pp, y_pm, y_mp, y_mm});

        fitout << tt << " " << yfit << " " << y_min << " " << y_max << "\n";
    }

    fitout.close();

    return 0;

}

    // std::ofstream fitfile("fit.txt");

    // for(double z=0; z<=16; z+=0.1){

    //     double fit = a*std::exp(-lambda*z);

    //     fitfile
    //         << z << " "
    //         << fit << "\n";
    // }

    // std::ofstream f("fit_band.txt");

    // for(double t=0; t<=16; t+=0.1){

    //     auto F = [&](double LN_A, double Lambda){
    //         return LN_A*std::exp(-Lambda*t);
    //     };

    //     double f0 = F(ln_a, lambda);

    //     double fpp = F(ln_a+d_ln_a, lambda+d_lambda);
    //     double fpm = F(ln_a+d_ln_a, lambda-d_lambda);
    //     double fmp = F(ln_a-d_ln_a, lambda+d_lambda);
    //     double fmm = F(ln_a-d_ln_a, lambda-d_lambda);

    //     f << t << " "
    //     << f0  << " "
    //     << fpp << " "
    //     << fpm << " "
    //     << fmp << " "
    //     << fmm << "\n";
    // }