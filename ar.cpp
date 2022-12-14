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
    int p = 3;
    double phi[p] = {0.8, 0.05, 0.05};

    // Make file for sample
    std::ofstream AR;
    AR.open ("AR.csv");

    // Set X to zero to avoid strange happenings
    for(int i = 0; i < n; i++){
        X[i] = 0;
    }

    // Generate the AR(p) process: X_t = (sum{i=1...p} X_(t-i) * phi_i) + noise_t
    for(int i = 0; i < n; i++){
        noise[i] = normal_dist(e);
        for(int j = 0; j < p; j++){
            X[i] += X[i - (j + 1)] * phi[j];
        }
        X[i] += noise[i];
        AR << X[i] << ","; // Write
    }

    AR.close();
    std::cout << "Done." << std::endl;
    return 0;
}

