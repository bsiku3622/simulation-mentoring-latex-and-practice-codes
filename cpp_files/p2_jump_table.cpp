#include <iostream>
#include <vector>
#include <chrono>
#include <random>

enum ParticleType {
    TYPE_A = 0,
    TYPE_B,
    TYPE_C,
    TYPE_D,
    TYPE_E,
    TYPE_COUNT
};

struct Particle {
    double x, v;
    ParticleType type;
};

// 임의 가속도 계산 함수
double computeAcceleration_if(ParticleType type) {
    if (type == TYPE_A) return 0.1;
    else if (type == TYPE_B) return 0.2;
    else if (type == TYPE_C) return 0.3;
    else if (type == TYPE_D) return 0.4;
    else return 0.5; // TYPE_E
}

double computeAcceleration_switch(ParticleType type) {
    switch (type) {
        case TYPE_A: return 0.1;
        case TYPE_B: return 0.2;
        case TYPE_C: return 0.3;
        case TYPE_D: return 0.4;
        case TYPE_E: return 0.5;
        default: return 0.0;
    }
}

int main() {
    const int N = 1000000;
    const int steps = 1000;
    const double dt = 0.01;

    std::vector<Particle> particles(N);

    // 입자 초기화
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(-10.0, 10.0);
    std::uniform_int_distribution<int> type_dist(0, TYPE_COUNT-1);

    for (auto& p : particles) {
        p.x = dist(rng);
        p.v = dist(rng);
        p.type = static_cast<ParticleType>(type_dist(rng));
    }

    // ---------- if-else 버전 ----------
    auto start_if = std::chrono::high_resolution_clock::now();

    for (int step = 0; step < steps; ++step) {
        for (auto& p : particles) {
            double a = computeAcceleration_if(p.type);
            p.v += a * dt;
            p.x += p.v * dt;
        }
    }

    auto end_if = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dur_if = end_if - start_if;
    std::cout << "if-else time: " << dur_if.count() << " s\n";

    // ---------- switch 버전 ----------
    // 입자 초기화 다시
    for (auto& p : particles) {
        p.x = dist(rng);
        p.v = dist(rng);
        p.type = static_cast<ParticleType>(type_dist(rng));
    }

    auto start_switch = std::chrono::high_resolution_clock::now();

    for (int step = 0; step < steps; ++step) {
        for (auto& p : particles) {
            double a = computeAcceleration_switch(p.type);
            p.v += a * dt;
            p.x += p.v * dt;
        }
    }

    auto end_switch = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dur_switch = end_switch - start_switch;
    std::cout << "switch time: " << dur_switch.count() << " s\n";

    return 0;
}
