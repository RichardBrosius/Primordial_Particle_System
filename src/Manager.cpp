#include "Manager.h"
// https://stackoverflow.com/questions/13026523/undefined-symbol-error-importing-cython-module
#include "Particle.cpp"

namespace particles {


    Manager::Manager(){

        this->substrate = new Particle[2]; 
    }

    Manager::~Manager(){   
    }

    void Manager::initialize(int n_particles){
        this->n_particles = n_particles;

        double* p1_pos = new double[2];
        p1_pos[0] = 1;
        p1_pos[1] = 2;

        double* p2_pos = new double[2];
        p2_pos[0] = 3;
        p2_pos[1] = 4;


        Particle* p1 = new Particle(1, p1_pos, 1.0, 180);
        Particle* p2 = new Particle(1, p2_pos, 1.0, 180);

        this->substrate[0] = *p1;
        this->substrate[1] = *p2;


    }

    

    void Manager::sense(void){

    }
    
    void Manager::move(double dt){
        for(int i=0; i < this->n_particles; i++)
        {
            (this->substrate[i]).move(1);
        }


    }

    void Manager::orient(double dt){

    }

    double ** Manager::get_positions(void){

        int rows = this->n_particles, cols = 2;
        double** positions = new double*[rows];
        for(int i = 0; i < rows; ++i){
            positions[i] = new double[cols];
            positions[i][0] = (this->substrate[i]).position()[0];
            positions[i][1] = (this->substrate[i]).position()[1];
            //[i][0] = 1;
            //positions[i][1] = 2;

            std::cout << "x: " << positions[i][0] << "\ty: " << positions[i][1] << std::endl;

        }



        return positions;
    }

}

