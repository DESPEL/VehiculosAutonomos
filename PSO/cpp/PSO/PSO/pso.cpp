#include <array>
#include <random>
#include <iostream>

//#include "fast_matrix.cpp"
#include "matrix.cpp"

#include <stdlib.h>

int numOfHeapAllocations = 0;

void* operator new(size_t size)
{
    numOfHeapAllocations++;
    return malloc(size);
}

// idk, 
double testFunc(Matrix<double, 1, 2>& mat) {
    auto &[x, y] = mat[0];
	return x * x + y * y * 10000;
}

// definition
const int dimensions = 2;
Matrix<double, 1, dimensions> v_size;

const int var_min = -10;
const int var_max = 10;

// parameters
const int max_iterations = 100;
const int swarm_size = 50;
double inertia_coefficient = 1;
const double personal_acceleration_coefficient = 2;
const double social_acceleration_coefficient = 2;
const double inertia_coefficient_damp = 0.99;

// initialization

struct Best {
    Matrix<double, 1, dimensions> position;
    double cost;
};

struct Particle {
    Matrix<double, 1, dimensions> position;
    Matrix<double, 1, dimensions> velocity;
    double cost;
    Best best;
};


std::array<Particle, swarm_size> population; 

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> r_pos(var_min, var_max);

    Best global_best;
    global_best.cost = INFINITY;

    for (auto& particle: population) {
        particle.position.fill([&]() {
            return r_pos(gen);
        });
        particle.cost = testFunc(
            particle.position
        );
        particle.velocity.fill([&]() {
            return 0.0;
        });

        particle.best.position = particle.position;
        particle.best.cost = particle.cost;

        if (particle.cost < global_best.cost)
            global_best = particle.best;
    }


    std::array<Best, max_iterations> best_costs;
    // main_loop
    std::uniform_real_distribution<> r_0_1(0, 1);

    for (auto& b_cost: best_costs) {
        for (auto& particle: population) {
            Matrix<double, 1, 2> random_matrix1;
            random_matrix1.fill([&]() {
                return r_0_1(gen);
            });
            Matrix<double, 1, 2> random_matrix2;
            random_matrix2.fill([&]() {
                return r_0_1(gen);
            });

            particle.velocity = 
                particle.velocity
                * inertia_coefficient
                + random_matrix1.dot_product(
                    particle.best.position
                    - particle.position
                )
                + random_matrix2.dot_product(
                    global_best.position
                    - particle.position
                );
            
            particle.position = particle.position + particle.velocity;

            particle.cost = testFunc(particle.position);

            if (particle.cost < particle.best.cost) {
                particle.best.cost = particle.cost;
                particle.best.position = particle.position;

                if (particle.cost < global_best.cost)
                    global_best = particle.best;
            }
        }
        inertia_coefficient = inertia_coefficient * inertia_coefficient_damp;

        b_cost = global_best;
        //std::cout << global_best.cost << '\n';
    }
    std::cout << "memory allocations: " << numOfHeapAllocations << '\n';
}
