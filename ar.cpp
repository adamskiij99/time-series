#include <iostream>
#include <random>
#include <fstream>

int main()
{
    std::random_device r;
    std::default_random_engine e(r());
    std::normal_distribution<> normal_dist(0, 1);

    int n = 1000;
    double noise[n];
    double X[n];
    int p = 3;
    double params[p] = {0.1, 0.2, 0.1};

    std::ofstream AR;
    AR.open ("AR.csv");

    for(int i = 0; i < n; i++){
        noise[i] = normal_dist(e);
        for(int j = 0; j < p; j++){
            X[i] += X[i - (j + 1)] * params[j];
        }
        X[i] += noise[i];
        AR << X[i] << ",";
    }

    AR.close();

    std::cout << "Done." << std::endl;
}

