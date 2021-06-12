#include "Particle.h"

namespace particles {

    // Default constructor
    Particle::Particle () {}


    Particle::Particle (int pid, double* pos, double speed, double phi) {
        this->pos = pos;
        this->phi = phi;
        this->speed = speed;
        this->pid = pid;

        this->color = new double[3];
        this->color[0] = 0;   // Red
        this->color[1] = 0;   // Green
        this->color[2] = 255; // Blue

        this->n_left = 0;
        this->n_right = 0;
        this->alpha = 180;
        this->beta = 17;
        this->domain = 5;

    }

    Particle::~Particle() {

        //delete[] this->color;
    }

    void Particle::move(double dt){}

    void Particle::orient(double dt){}

//    int* Particle::sense(void){

//        int* counts = new int[2];
//       counts[0] = 0;
//        counts[1] = 1;

//        return counts;
//    }




}