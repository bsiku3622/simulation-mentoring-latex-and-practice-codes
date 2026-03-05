#include <iostream>
#include <cmath>
#include <iomanip>

// 테일러 급수로 e^x 근사
double taylor_exp(double x, int n) {
    double sum = 1.0;
    double term = 1.0;
    for (int i = 1; i <= n; ++i) {
        term *= x / i;
        sum += term;
    }
    return sum;
}

int main() {
    double x = 1.0;
    double actual = std::exp(x);

    std::cout << "Target: e^" << x << " = " << std::fixed << std::setprecision(15) << actual << "\n\n";
    std::cout << std::setw(5) << "N" << std::setw(20) << "Approx" << std::setw(20) << "Error" << "\n";
    std::cout << "---------------------------------------------\n";

    for (int n = 1; n <= 15; ++n) {
        double approx = taylor_exp(x, n);
        double error = std::abs(actual - approx);
        std::cout << std::setw(5) << n << std::setw(20) << approx << std::setw(20) << error << "\n";
    }

    return 0;
}
