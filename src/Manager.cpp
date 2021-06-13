#include "Manager.h"
// https://stackoverflow.com/questions/13026523/undefined-symbol-error-importing-cython-module
#include "Particle.cpp"
#include <stdlib.h>

namespace particles {


    Manager::Manager(){

    }

    Manager::~Manager(){   
    }

    void Manager::initialize(int n_particles, int seed){
        this->n_particles = n_particles;
        this->substrate = new Particle[n_particles];
        double* p1_pos;

        srand(seed);

        for(int i = 0; i < n_particles; i++){
            p1_pos = new double[2];
            p1_pos[0] = (rand() % 250) / 1;
            p1_pos[1] = (rand() % 250) / 1;
            Particle* p1 = new Particle(1, p1_pos, .67, rand() % 360);

            this->substrate[i] = *p1;

        }

    }

    

    void Manager::sense(void){

        double** positions = new double* [this->n_particles];
        double* position = new double[2];
        int* result = new int[2];

        for(int i=0; i < n_particles; i++){
            positions[i] = new double[2];
            position = (this->substrate[i]).position();

            positions[i][0] = position[0];
            positions[i][1] = position[1];
        }

        for(int i=0; i < n_particles; i++){
            result = (this->substrate[i]).sense(positions, this->n_particles);
            //std::cout << result[0] << "," << result[1] << std::endl;
        }
   

    }
    
    void Manager::move(double dt){
        for(int i=0; i < this->n_particles; i++)
        {
            (this->substrate[i]).move(1);
        }


    }

    void Manager::orient(double dt){
        for(int i=0; i < this->n_particles; i++)
        {
            (this->substrate[i]).orient(1);
        }

    }

    double** Manager::get_positions(void){

        int rows = this->n_particles, cols = 2;
        double** positions = new double*[rows];
        for(int i = 0; i < rows; ++i){
            positions[i] = new double[cols];
            positions[i][0] = (this->substrate[i]).position()[0];
            positions[i][1] = (this->substrate[i]).position()[1];
            // std::cout << "x: " << positions[i][0] << "\ty: " << positions[i][1] << std::endl;
        }

        return positions;
    }

    int** Manager::get_colors(void){

        int rows = this->n_particles, cols = 3;
        int** colors = new int*[rows];
        for(int i = 0; i < rows; ++i){
            colors[i] = new int[cols];
            colors[i][0] = (this->substrate[i]).color[0];
            colors[i][1] = (this->substrate[i]).color[1];
            colors[i][2] = (this->substrate[i]).color[2];

         }
        
        return colors;

    }

}

