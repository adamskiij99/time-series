#include <iostream>
#include <random>
#include <fstream>
#include <vector>

std::vector<double> differenced(std::vector<double> X, int d){
    int size = X.size();
    std::vector<double> Y = X;

    for (int j = 0; j < d; j++){
        for(int i = 0; i < size - 1; i++){
        Y[i] = Y[i + 1] - Y[i];
        }
    }

    return Y;
}

std::vector<double> undo_difference(std::vector<double> Y, int d){
    int sy = Y.size();
    int sx = sy + d;
    std::vector<double> b(sx, 0);
    std::vector<double> X = b;

    for(int i = 0; i < sy; i++){
        X[i] = Y[i];
    }

    for(int j = 0; j < d; j++){
        for(int i = 0; i < sy + j; i++){
            b[i] = X[i];
        }

        for(int i = 0; i < sx - 1; i++){
            X[i + 1] = X[i] + b[i];
        }
    }

    return X;
}

/*
int main(){
    std::vector<double> X = {1, 2, 4, 5, 7, 8, 12, 14, 19, 25};
    for(int i = 0; i < 10; i++){
        std::cout << X[i] << " ";
    }
    std::cout << std::endl << " ";

    int d = 0;

    std:: vector<double> Y = differenced(X, d);
    
    std::vector<double> Z = undo_difference(Y, d);

    for(int i = 0; i < 10 - d; i++){
        std::cout << Y[i] << " ";
    }
    std::cout << std::endl;

    for(int i = 0; i < 10; i++){
        std::cout << Z[i] << " ";
    }
    std::cout << std::endl << std::endl;

    std::vector<double> test_Y(10, 1);
    int dd = 3;
    std::vector<double> test_Z = undo_difference(test_Y, dd);
    for(int i = 0; i < 10 + dd; i++){
        std::cout << test_Z[i] << " ";
    }

    return 0;
}
*/

int main()
{
    // Set up random number generation
    std::random_device r;
    std::default_random_engine e(r());
    std::normal_distribution<> normal_dist(0, 1);

    // Initialise
    int n = 500;
    int d = 1;
    std::vector<double> X(n + d, 0);
    std::vector<double> noise(n, 0);
    int p = 2;
    int q = 1;
    double mu = 0;
    std::vector<double> phi = {0.45, 0.045};
    std::vector<double> theta = {0.13};

    for(int i = 0; i < n; i++){
        noise[i] = normal_dist(e);
    }

    // Generate the ARIMA(p, q) process: X_t = mu + (sum{i=1...p} X_(t-i) * phi_i) + (sum{i=1...q} noise_(t-i) * theta_i) + noise_t
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
        //ARIMA << X[i] << ","; // Write
    }

    std::vector<double> X_int = undo_difference(X, d);

    // Make file for sample
    std::ofstream ARIMA;
    ARIMA.open ("ARIMA.csv");

    for(int i = 0; i < n + d; i++){
        ARIMA << X_int[i] << ",";
    }

    ARIMA.close();
    std::cout << "Done." << std::endl;
    return 0;
}
