#include <iostream>
#include <random>
#include <fstream>

int main()
{
    // Set up random number generation
    std::random_device r;
    std::default_random_engine e(r());
    std::normal_distribution<> normal_dist(0, 1);

    // Initialise
    int n = 500;
    double noise[n];
    double X[n];
    int q = 3;
    double mu = 5;
    double theta[q] = {0.8, 0.05, 0.05};

    // Make file for sample
    std::ofstream MA;
    MA.open ("MA.csv");

    // Set X to (mostly) zero to avoid strange happenings
    for(int i = 0; i < n; i++){
        X[i] = 0;
        noise[i] = normal_dist(e);
    }

    // Generate the MA(q) process: X_t = mu + (sum{i=1...q} noise_(t-i) * theta_i) + noise_t
    for(int i = 0; i < n; i++){
        for(int j = 0; j < q; j++){
            X[i] += noise[i - (j + 1)] * theta[j];
        }
        X[i] += mu + noise[i];
        MA << X[i] << ","; // Write
    }

    MA.close();
    std::cout << "Done." << std::endl;
    return 0;
}

