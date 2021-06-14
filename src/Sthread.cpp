

#include "Sthread.h"
#include "Particle.h"


namespace particles{


class Particle;


    void SThread::operator() (Particle* substrate, int n_particles, int start, int end)
    {

            
            //std::cout << "Hellow from thread: " << start << ":" << end << std::endl;
            int interval = end - start;

            double** positions = new double* [n_particles];
            double* position = new double[2];
            int* result = new int[2];

            for(int i=0; i < n_particles; i++){
                positions[i] = new double[2];
                position = (substrate[i]).position();

                positions[i][0] = position[0];
                positions[i][1] = position[1];
            }

            for(int i=start; i < end; i++){
                result = (substrate[i]).sense(positions, n_particles);
                //std::cout << result[0] << "," << result[1] << std::endl;
            }
    
            for(int i = 0; i < n_particles; i++){
                delete[] positions[i];
            }

            // delete[] position;
            // delete[] result;


    }
}