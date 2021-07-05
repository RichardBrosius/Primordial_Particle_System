#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include "Particle.h"


namespace particles {
 class Manager {

 public: 

   Manager();
   Manager(int x_size, int y_size);
   ~Manager();
   void initialize(int n_particles, int seed);
   void sense(void);
   void move(double dt);
   void orient(double dt);
   double* get_positions(void);
   int* get_colors(void);
   void free_positions(void);
   void free_colors(void);
   int regulate(int t, double target_density); // Returns number of particles to add
   void create_particles(int n_particles);


    int n_particles;
    Particle* substrate;
    double* positions_ptr;
    int* colors_ptr;
    std::vector<double> gpd[10];
    int x_size;
    int y_size;




 };

}
#endif