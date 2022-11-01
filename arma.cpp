#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    // Set up random number generation
    std::random_device r;
    std::default_random_engine e(r());
    std::normal_distribution<> normal_dist(0, 1);

    // Initialise
    int n = 500;
    std::vector<double> noise(n, 0);
    std::vector<double> X(n, 0);
    int p = 2;
    int q = 3;
    double mu = 1;
    double phi[p] = {0.45, 0.45};
    double theta[q] = {0.3, 0.05, 0.05};

    // Make file for sample
    std::ofstream ARMA;
    ARMA.open ("ARMA.csv");

    // Set X to zero to avoid strange happenings and initialise noise
    for(int i = 0; i < n; i++){
        X[i] = 0;
        noise[i] = normal_dist(e);
    }

    // Generate the ARMA(p, q) process: X_t = mu + (sum{i=1...p} X_(t-i) * phi_i) + (sum{i=1...q} noise_(t-i) * theta_i) + noise_t
    for(int i = 0; i < n; i++){
        for(int j = 0; j < p; j++){
            if(i - (j + 1) > -1){
                X[i] += X[i - (j + 1)] * phi[j];
            }
        }
        for(int j = 0; j < q; j++){
            if(i - (j + 1) > -1){
                X[i] += noise[i - (j + 1)] * theta[j];
            }
        }
        X[i] += mu + noise[i];
        ARMA << X[i] << ","; // Write
    }

    ARMA.close();
    std::cout << "Done." << std::endl;
    return 0;
}

