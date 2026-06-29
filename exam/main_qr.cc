#include <iostream>
#include <random>
#include <string>

#include "matrix.h"
#include "qr.h"

using namespace pp;

matrix random_matrix(int n)
{
    matrix A(n,n);

    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(0.0,1.0);

    for(int j=0;j<n;j++)
        for(int i=0;i<n;i++)
            A(i,j)=dist(gen);

    return A;
}

int main(int argc,char** argv)
{
    int n = 100;

    if(argc > 2 && std::string(argv[1]) == "-size")
        n = std::stoi(argv[2]);

    matrix A = random_matrix(n);

    qr QR(A);

    return 0;
}