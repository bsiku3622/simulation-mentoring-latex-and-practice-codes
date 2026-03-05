#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>  // system() 사용

int main() {
    const int N = 100;       // 격자 포인트 수
    const double L = 1.0;    // 길이
    const double dx = L / (N-1);
    const double dt = 0.0005; 
    const int steps = 20001;  

    const double alpha = 0.01; // 열 확산 계수

    std::vector<double> u(N, 0.0);    // 현재 온도
    std::vector<double> u_temp(N, 0.0);
    std::vector<double> u_new(N, 0.0);// 업데이트된 온도

    // 초기 조건: 가운데에 열점
    u[N/2] = 1.0;

    // 시뮬레이션
    for (int step = 0; step < steps; ++step) {
        for (int i = 1; i < N-1; ++i) {
            // double d2u_dx2 = (u[i+1] - 2*u[i] + u[i-1]) / (dx*dx);
            
            double d2u_dx2 = (u[i+1] - 2*u[i] + u[i-1]) / (dx*dx);
            
            u_temp[i] = u[i] + alpha * dt * d2u_dx2;
        }
        u_temp[0] = u_temp[1];
        u_temp[N-1] = u_temp[N-2];

        for (int i = 1; i < N-1; ++i) {
            double d2u_dx2 = (u[i+1] - 2*u[i] + u[i-1]) / (dx*dx);
            double d2u_temp_dx2 = (u_temp[i+1] - 2*u_temp[i] + u_temp[i-1]) / (dx*dx);
            u_new[i] = u[i] + alpha * dt * 0.5 * (d2u_dx2 + d2u_temp_dx2);
        }

        // 경계조건: Dirichlet 0
        u_new[0] = u_new[1];
        u_new[N-1] = u_new[N-2];

        // 업데이트
        u = u_new;


        // 결과 저장 및 gnuplot 출력 (100 step마다)
        if (step % 100 == 0) {
            std::string filename = "data_" + std::to_string(step) + ".txt";
            std::ofstream out(filename);
            for (int i = 0; i < N; ++i) {
                out << i*dx << " " << u[i] << "\n";
            }
            out.close();
        }
    }

    return 0;
}
