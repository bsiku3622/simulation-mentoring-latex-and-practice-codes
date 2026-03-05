#include <iostream>
#include <chrono>
#include <vector>
#include <random>

struct Particle {
    double x, v;
};

// 시뮬레이션 파라미터
const int N = 100000; // 입자 수
const int steps = 5000;
const double dt = 0.01;

// 스택 기반 시뮬레이션
void simulate_stack() {
    Particle particles[N]; // 스택에 할당

    // 초기화
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);
    for (auto& p : particles) {
        p.x = dist(rng);
        p.v = dist(rng);
    }

    // 시뮬레이션
    for (int step = 0; step < steps; ++step) {
        for (auto& p : particles) {
            p.v += 0.01; // 임의 가속도
            p.x += p.v * dt;
        }
    }
}

// 힙 기반 시뮬레이션
void simulate_heap() {
    std::vector<Particle> particles(N); // 힙에 할당

    // 초기화
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);
    for (auto& p : particles) {
        p.x = dist(rng);
        p.v = dist(rng);
    }

    // 시뮬레이션
    for (int step = 0; step < steps; ++step) {
        for (auto& p : particles) {
            p.v += 0.01; // 임의 가속도
            p.x += p.v * dt;
        }
    }
}

int main() {
    auto start_stack = std::chrono::high_resolution_clock::now();
    simulate_stack();
    auto end_stack = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dur_stack = end_stack - start_stack;
    std::cout << "Stack simulation time: " << dur_stack.count() << " s\n";

    auto start_heap = std::chrono::high_resolution_clock::now();
    simulate_heap();
    auto end_heap = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dur_heap = end_heap - start_heap;
    std::cout << "Heap simulation time: " << dur_heap.count() << " s\n";

    return 0;
}
