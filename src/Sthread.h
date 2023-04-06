#ifndef STHREAD_H
#define STHREAD_H

#include "Particle.h"

namespace particles{

    class SThread{

        public:

        void operator() (Particle* substrate, int n_particles, int start, int end);


    };
}



#endif