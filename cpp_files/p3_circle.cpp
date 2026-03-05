#include <iostream>
#include <fstream>
#include <cmath>

int main() {
    const double PI = 3.14159265359;
    const double radius = 5.0;
    const double velocity = 1.0;
    const int steps = 628 * 100;     // 2*PI / 0.01
    const double dt = 0.01;          // time step
    
    std::ofstream outfile("data.txt");
    
    if (!outfile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    
    // Write header for gnuplot
    outfile << "# Circular Motion Trajectory" << std::endl;
    outfile << "# time\tx\ty\tcolor" << std::endl;
    
    double t = 0.0;
    double x = radius, y = 0, vx = 0, vy = velocity, ax = 0, ay = 0;

    for (int i = 0; i < steps; i++) {
        ax = - (velocity * velocity / radius) * (x / radius);
        ay = - (velocity * velocity / radius) * (y / radius);

        vx += ax * dt;
        vy += ay * dt;
        x += vx * dt;
        y += vy * dt;
        t += dt;

        // 색상 값: 0~1 범위로 정규화
        double color = static_cast<double>(i) / steps;

        outfile << t << "\t" << x << "\t" << y << "\t" << color << std::endl;
    }
    
    outfile.close();
    std::cout << "Trajectory saved to data.txt" << std::endl;
    
    return 0;
}