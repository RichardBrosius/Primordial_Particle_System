

#include "Sthread.h"
#include "Particle.h"


namespace particles{


class Particle;


    void SThread::operator() (Particle* substrate, int n_particles, int start, int end)
    {

            

            double** positions = new double* [n_particles];
            double* position = new double[2];

            for(int i=0; i < n_particles; i++){
                positions[i] = new double[2];
                position = (substrate[i]).get_position();

                positions[i][0] = position[0];
                positions[i][1] = position[1];
            }

            for(int i=start; i < end; i++){
                (substrate[i]).sense(positions, n_particles);
            }
    
            for(int i = 0; i < n_particles; i++){
                delete[] positions[i];
            }
            delete positions;


    }
}