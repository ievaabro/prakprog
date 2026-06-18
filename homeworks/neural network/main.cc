#include <cmath>
#include <fstream>
#include "nn.h"

double g(double x){

    return cos(5*x-1)*exp(-x*x);
}

int main(){

    int N = 40;

    pp::vector xs(N), ys(N);

    for(int i=0;i<N;i++){

        double x = -1 + 2.0*i/(N-1);

        xs[i] = x;

        ys[i] = g(x);
    }

    ann network(10);

    network.train(xs,ys);

    std::ofstream out("ann.data");

    for(double x=-1;x<=1;x+=0.01){

        out
        << x << " "
        << g(x) << " "
        << network.response(x)
        << "\n";
    }

    std::ofstream Bout("ann_opgB.data");

    for(double x=-1;x<=1;x+=0.01){

        Bout
        << x << " "
        << g(x) << " "
        << network.response(x) << " "
        << network.derivative(x) << " "
        << network.second_derivative(x) << " "
        << network.antiderivative(x)
        << "\n";
    }

    return 0;
}