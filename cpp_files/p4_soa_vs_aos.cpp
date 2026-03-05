#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>

const int N = 1000000; // 입자 수
const int STEPS = 100; // 시뮬레이션 스텝
const float dt = 0.01f;

// AoS
struct Particle {
    float x, y;
    float vx, vy;
};

void simulateAoS(std::vector<Particle>& particles) {
    for(int s = 0; s < STEPS; ++s) {
        for(int i = 1; i < N; ++i) { // 이전 입자의 위치를 참조
            float dx = particles[i].x - particles[i-1].x;
            float dy = particles[i].y - particles[i-1].y;
            float dist2 = dx*dx + dy*dy + 1e-6f;
            float force = 1.0f / dist2;
            float dist = std::sqrt(dist2);

            particles[i].vx -= force * dx / dist * dt;
            particles[i].vy -= force * dy / dist * dt;

            particles[i].x += particles[i].vx * dt;
            particles[i].y += particles[i].vy * dt;
        }
    }
}

// SoA
struct ParticleSoA {
    std::vector<float> x, y;
    std::vector<float> vx, vy;
};

void simulateSoA(ParticleSoA& particles) {
    for(int s = 0; s < STEPS; ++s) {
        for(int i = 1; i < N; ++i) {
            float dx = particles.x[i] - particles.x[i-1];
            float dy = particles.y[i] - particles.y[i-1];
            float dist2 = dx*dx + dy*dy + 1e-6f;
            float force = 1.0f / dist2;
            float dist = std::sqrt(dist2);

            particles.vx[i] -= force * dx / dist * dt;
            particles.vy[i] -= force * dy / dist * dt;

            particles.x[i] += particles.vx[i] * dt;
            particles.y[i] += particles.vy[i] * dt;
        }
    }
}

int main() {
    std::vector<Particle> particlesAoS(N);
    ParticleSoA particlesSoA;
    particlesSoA.x.resize(N);
    particlesSoA.y.resize(N);
    particlesSoA.vx.resize(N);
    particlesSoA.vy.resize(N);

    // 초기값 랜덤
    std::mt19937 rng(123);
    std::uniform_real_distribution<float> dist(-10.0f, 10.0f);

    for(int i = 0; i < N; ++i) {
        float x = dist(rng), y = dist(rng), vx = dist(rng), vy = dist(rng);
        particlesAoS[i] = {x, y, vx, vy};
        particlesSoA.x[i] = x;
        particlesSoA.y[i] = y;
        particlesSoA.vx[i] = vx;
        particlesSoA.vy[i] = vy;
    }

    auto start = std::chrono::high_resolution_clock::now();
    simulateAoS(particlesAoS);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "AoS Time: "
              << std::chrono::duration<float>(end - start).count() << "s\n";

    start = std::chrono::high_resolution_clock::now();
    simulateSoA(particlesSoA);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "SoA Time: "
              << std::chrono::duration<float>(end - start).count() << "s\n";

    return 0;
}
