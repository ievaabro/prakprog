#include <cmath>
#include "nn.h"

ann::ann(int n_){ // Contructor

    n = n_;
    p.resize(3*n);

    for(int i=0;i<n;i++){

        p[3*i+0] = -1 + 2.0*i/(n-1);
        p[3*i+1] = 0.5;
        p[3*i+2] = 1.0;
    }
}

double ann::activation(double x){ // Activation function

    return x*exp(-x*x);
}

double ann::activation_derivative(double x){ // Derivative

    return exp(-x*x)*(1 - 2*x*x);
} 

double ann::activation_second_derivative(double x){

    return exp(-x*x)*(4*x*x*x - 6*x);
}

double ann::activation_antiderivative(double x){

    return -0.5*exp(-x*x);
}

double ann::response(double x){ // Response

    double sum = 0;

    for(int i=0;i<n;i++){

        double a = p[3*i+0];
        double b = p[3*i+1];
        double w = p[3*i+2];
        double z = (x-a)/b;

        sum += w*activation(z);
    }

    return sum;
}

double ann::derivative(double x){

    double sum = 0;

    for(int i=0;i<n;i++){

        double a = p[3*i+0];
        double b = p[3*i+1];
        double w = p[3*i+2];
        double z = (x-a)/b;

        sum += w*activation_derivative(z)/b;
    }

    return sum;
}

double ann::second_derivative(double x){

    double sum = 0;

    for(int i=0;i<n;i++){

        double a = p[3*i+0];
        double b = p[3*i+1];
        double w = p[3*i+2];
        double z = (x-a)/b;

        sum += w* activation_second_derivative(z)/(b*b);
    }

    return sum;
}

double ann::antiderivative(double x){

    double sum = 0;

    for(int i=0;i<n;i++){

        double a = p[3*i+0];
        double b = p[3*i+1];
        double w = p[3*i+2];
        double z = (x-a)/b;

        sum +=w*b*activation_antiderivative(z);
    }

    return sum;
}

double ann::cost(pp::vector xs, pp::vector ys){ // Cost - to be minimized

    double sum = 0;

    for(int i=0;i<xs.size();i++){

        double d = response(xs[i]) - ys[i];
        sum += d*d;
    }

    return sum;
}

pp::vector ann::gradient(pp::vector xs, pp::vector ys){ // gradient

    pp::vector grad(3*n);

    for(int k=0;k<xs.size();k++){

        double x = xs[k];
        double y = ys[k];

        double Fx = response(x);

        double delta = Fx - y;

        for(int i=0;i<n;i++){

            double a = p[3*i+0];
            double b = p[3*i+1];
            double w = p[3*i+2];

            double z = (x-a)/b;

            double f  = activation(z);

            double fp = exp(-z*z)*(1 - 2*z*z);

            grad[3*i+2] += 2*delta*f;

            grad[3*i+0] += 2*delta*w*fp*(-1.0/b);

            grad[3*i+1] +=
                2*delta*w*fp*
                (-(x-a)/(b*b));
        }
    }

    return grad;
}

void ann::train(pp::vector xs, pp::vector ys){ // Trainer med gradient

    double lr = 1e-2;

    for(int step=0; step<10000; step++){

        pp::vector g = gradient(xs,ys);

        for(int i=0;i<p.size();i++){

            p[i] -= lr*g[i];
        }
    }
}