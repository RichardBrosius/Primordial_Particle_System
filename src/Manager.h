#ifndef MANAGER_H
#define MANAGER_H

#include "Particle.h"

namespace particles {
 class Manager {

 public: 

    Manager();
    ~Manager();
    void initialize(int n_particles, int seed);
    void sense(void);
    void move(double dt);
    void orient(double dt);
    double** get_positions(void);
    int** get_colors(void);
    void free_positions(void);
    void free_colors(void);

    int n_particles;
    Particle* substrate;
    double** positions_ptr;
    int** colors_ptr;




 };

}
#endif