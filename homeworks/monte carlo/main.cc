#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <random>

using namespace std;

class lcg {
public:
    unsigned long long seed;
    unsigned long long a, c, m;

    lcg(unsigned long long s,
        unsigned long long a_ = 1664525,
        unsigned long long c_ = 1013904223,
        unsigned long long m_ = 1ULL<<32) //pow(2,32))
    {
        seed = s;
        a = a_;
        c = c_;
        m = m_;
    }

    double operator()() {
        seed = (a * seed + c) % m;
        return (seed + 1.0)/(m + 1.0);
    }
};

pair<double,double> plainmc(
    double f(vector<double>),
    vector<double> a,
    vector<double> b,
    int N,
    lcg& rng
){
    int dim = a.size();

    double V = 1.0;
    for(int i=0;i<dim;i++)
        V *= (b[i]-a[i]);

    double sum1 = 0;
    double sum2 = 0;

    vector<double> x(dim);

    for(int k=0;k<N;k++){

        for(int i=0;i<dim;i++)
            x[i] = a[i] + rng()*(b[i]-a[i]);

        double fx = f(x);

        sum1 += fx;
        sum2 += fx*fx;
    }

    double mean = sum1/N;

    double sigma = sqrt(sum2/N - mean*mean);

    double integral = mean*V;
    double error = sigma*V/sqrt(N);

    return {integral,error};
}

double circle(vector<double> x){

    double r2 = x[0]*x[0] + x[1]*x[1];

    if(r2 <= 1.0)
        return 1.0;
    else
        return 0.0;
}

double ellipsoid(vector<double> x){

    double a = 1.0;
    double b = 2.0;
    double c = 3.0;

    double value =
        x[0]*x[0]/(a*a)
      + x[1]*x[1]/(b*b)
      + x[2]*x[2]/(c*c);

    if(value <= 1.0)
        return 1.0;
    else
        return 0.0;
}

double corput(int n, int base){

    double q = 0;
    double bk = 1.0/base;

    while(n > 0){
        q += (n % base)*bk;
        n /= base;
        bk /= base;
    }

    return q;
}

vector<double> halton(int n, int dim){

    int bases[] = {2,3,5,7,11,13,17,19};

    vector<double> x(dim);

    for(int i=0;i<dim;i++)
        x[i] = corput(n,bases[i]);

    return x;
}

pair<double,double> quasimc(
    double f(vector<double>),
    vector<double> a,
    vector<double> b,
    int N){
    int dim = a.size();

    double V = 1.0;

    for(int i=0;i<dim;i++)
        V *= (b[i]-a[i]);

    double sum1 = 0;
    double sum2 = 0;

    for(int n=1;n<=N;n++){

        vector<double> x = halton(n,dim);

        vector<double> y = halton(n,dim);

        // shift second sequence slightly
        for(int i=0;i<dim;i++)
            y[i] = fmod(y[i] + 0.5,1.0);

        for(int i=0;i<dim;i++){
            x[i] = a[i] + x[i]*(b[i]-a[i]);
            y[i] = a[i] + y[i]*(b[i]-a[i]);
        }

        sum1 += f(x);
        sum2 += f(y);
    }

    double I1 = V*sum1/N;
    double I2 = V*sum2/N;

    double error = fabs(I1-I2);

    return {I1,error};
}

double singular(vector<double> x){

    double X = x[0];
    double Y = x[1];
    double Z = x[2];

    return 1.0/(
        1
        - cos(X)*cos(Y)*cos(Z)
    )/(M_PI*M_PI*M_PI);
}

mt19937 gen(1234);
uniform_real_distribution<double> dist(0.0,1.0);

double rnd(){
    return dist(gen);
}

template<typename Random>
pair<double,double> plainmc(
    double f(vector<double>),
    vector<double> a,
    vector<double> b,
    int N,
    Random rnd
){
    int dim = a.size();

    double V = 1.0;

    for(int i=0;i<dim;i++)
        V *= (b[i]-a[i]);

    double sum1 = 0;
    double sum2 = 0;

    vector<double> x(dim);

    for(int k=0;k<N;k++){

        for(int i=0;i<dim;i++)
            x[i] = a[i] + rnd()*(b[i]-a[i]);

        double fx = f(x);

        sum1 += fx;
        sum2 += fx*fx;
    }

    double mean = sum1/N;

    double sigma =
        sqrt(sum2/N - mean*mean);

    return {
        mean*V,
        sigma*V/sqrt(N)
    };
}

int main(){

    lcg rng(1234);

    vector<double> a = {-1,-1};
    vector<double> b = { 1, 1};

    ofstream out("mc.dat");

    for(int N=100; N<=1000000; N*=2){

        auto result = plainmc(circle,a,b,N,rng);

        double integral = result.first;
        double estimated_error = result.second;

        double actual_error = fabs(integral - M_PI);

        cout
            << N << " "
            << integral << " "
            << estimated_error << " "
            << actual_error << endl;

        out
            << N << " "
            << estimated_error << " "
            << actual_error << endl;
    }

    out.close();

    vector<double> ae = {-1,-2,-3};
    vector<double> be = { 1, 2, 3};

    cout << "\nEllipsoid volume\n";

    ofstream out2("ellipsoid.dat");

    for(int N=100; N<=1000000; N*=2){

        auto result = plainmc(ellipsoid,ae,be,N,rng);

        double integral = result.first;
        double estimated_error = result.second;

        double exact = 8*M_PI;

        double actual_error = fabs(integral - exact);

        cout
            << N << " "
            << integral << " "
            << estimated_error << " "
            << actual_error << endl;

        out2
            << N << " "
            << estimated_error << " "
            << actual_error << endl;
    }

    out2.close();
    
    cout << "\nQuasi Random\n";

    vector<double> aq = {0,0,0};
    vector<double> bq = {M_PI,M_PI,M_PI};

    double exact = 1.3932039296856768;

    ofstream qout("compare.dat");

    for(int N=10; N<=100000; N*=2){

        auto lcg_result =
            plainmc(singular,aq,bq,N,rng);

        auto mt_result =
            plainmc(singular,aq,bq,N,rnd);

        auto quasi_result =
            quasimc(singular,aq,bq,N);

        double lcg_error =
            fabs(lcg_result.first - exact);

        double mt_error =
            fabs(mt_result.first - exact);

        double quasi_error =
            fabs(quasi_result.first - exact);

        qout
            << N << " "
            << lcg_error << " "
            << mt_error << " "
            << quasi_error << endl;

        cout
            << N << " "
            << lcg_error << " "
            << mt_error << " "
            << quasi_error << endl;
    }

    qout.close();

    return 0;
}