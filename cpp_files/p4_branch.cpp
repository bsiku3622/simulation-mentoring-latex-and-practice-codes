#include <iostream>
#include <vector>
#include <chrono>
#include <random>

struct Particle {
    double x, v;
};

int main() {
    const int N = 1000000;      // 입자 수
    const int steps = 1000;     // 시뮬레이션 스텝
    const double dt = 0.01;     // 시간 간격
    const double boundary = 10.0;

    std::vector<Particle> particles(N);

    // 입자 초기화
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(-boundary, boundary);
    for (auto& p : particles) {
        p.x = dist(rng);
        p.v = dist(rng);
    }

    // ---------- if-else 버전 ----------
    auto start_if = std::chrono::high_resolution_clock::now();

    for (int step = 0; step < steps; ++step) {
        for (auto& p : particles) {
            p.x += p.v * dt;
            if (p.x > boundary) {
                p.x = boundary;
                p.v = -p.v;
            } else if (p.x < -boundary) {
                p.x = -boundary;
                p.v = -p.v;
            }
        }
    }

    auto end_if = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dur_if = end_if - start_if;
    std::cout << "if-else time: " << dur_if.count() << " s\n";

    // ---------- 삼항 연산자 버전 ----------
    // 입자 초기화 다시
    for (auto& p : particles) {
        p.x = dist(rng);
        p.v = dist(rng);
    }

    auto start_ternary = std::chrono::high_resolution_clock::now();

    for (int step = 0; step < steps; ++step) {
        for (auto& p : particles) {
            p.x += p.v * dt;
            p.v = (p.x > boundary) ? -p.v :
                  (p.x < -boundary) ? -p.v : p.v;
            p.x = (p.x > boundary) ? boundary :
                  (p.x < -boundary) ? -boundary : p.x;
        }
    }

    auto end_ternary = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dur_ternary = end_ternary - start_ternary;
    std::cout << "ternary time: " << dur_ternary.count() << " s\n";

    return 0;
}
