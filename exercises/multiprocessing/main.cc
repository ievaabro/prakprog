#include <iostream>
#include <vector>
#include <thread>
#include <string>

struct data {
    int a, b;
    double sum;
};

// Thread function
void harm(data& arg) {
    int a = arg.a, b = arg.b;
    double sum = 0;

    for (int i = a; i < b; i++) {
        sum += 1.0 / i;
    }

    arg.sum = sum; 
}

int main(int argc, char** argv) {

    int nthreads = 1;
    int nterms = (int)1e8;

    // Read command line arguments
    for (int i = 0; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-threads" && i + 1 < argc)
            nthreads = std::stoi(argv[i + 1]);
        if (arg == "-terms" && i + 1 < argc)
            nterms = std::stoi(argv[i + 1]);
    }

    std::vector<data> params(nthreads);

    for (int i = 0; i < nthreads; i++) {
        params[i].a = 1 + nterms / nthreads * i;
        params[i].b = 1 + nterms / nthreads * (i + 1);
        params[i].sum = 0;
    }

    // fix last interval
    params[nthreads - 1].b = nterms + 1;

    // Create threads
    std::vector<std::thread> threads;
    threads.reserve(nthreads);

    for (int i = 0; i < nthreads; i++) {
        threads.emplace_back(harm, std::ref(params[i]));
    }

    // Join threads
    for (auto& t : threads) {
        t.join();
    }

    // result
    double total = 0;
    for (auto& p : params) {
        total += p.sum;
    }

    std::cout << "Harmonic sum = " << total << std::endl;

    return 0;
}