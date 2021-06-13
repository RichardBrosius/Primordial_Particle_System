#ifndef MANAGER_H
#define MANAGER_H

#include "Particle.h"

namespace particles {
 class Manager {

 public: 

    Manager();
    ~Manager();
    void initialize(int n_particles);
    void sense(void);
    void move(double dt);
    void orient(double dt);
    double** get_positions(void);

    int n_particles;
    Particle* substrate;




 };

}
#endif