#include "Manager.h"
// https://stackoverflow.com/questions/13026523/undefined-symbol-error-importing-cython-module

// Must be added when used in cython
#include "Particle.cpp"
#include "Sthread.cpp"


#include "Sthread.h"
#include <stdlib.h>
#include <thread>





namespace particles {

    class Particle;

    Manager::Manager(){

    }

    Manager::~Manager(){   
        // delete[] this->substrate;
    
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
            Particle* p1 = new Particle(i, p1_pos, .67, rand() % 360);

            this->substrate[i] = *p1;

        }

    }

    

    void Manager::sense(void){

        int NUM_CORES = 8;
        int divisions[ NUM_CORES + 1];

        int division = this->n_particles / NUM_CORES;
        int remainder = this->n_particles % NUM_CORES;


        // Split the particles into equal group to be run on seperate threads

        for( int i=0; i <= NUM_CORES + 1; ++i){
            divisions[i] = i * division;
        }
    
        for(int i = 0; i < NUM_CORES; i++)
        {   
            if( i < remainder )
            {   divisions[i + 1] += i;}
            else if ( i >= remainder and i < NUM_CORES)
            {   divisions[i+1] += remainder;    }
        }



        std::thread threads[NUM_CORES];

        for(int thread=0; thread<NUM_CORES; ++thread)
        {
            threads[thread] = std::thread(SThread(), this->substrate, this->n_particles, divisions[thread], divisions[thread + 1]);
        }

        for(int i=0; i<NUM_CORES; ++i)
        {
            threads[i].join();
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

    double* Manager::get_positions(void){

        int rows = this->n_particles, cols = 2;
        positions_ptr = new double[rows * cols];
        for(int i = 0; i < rows; ++i){
            positions_ptr[cols*i] = (this->substrate[i]).position()[0];
            positions_ptr[cols*i+1] = (this->substrate[i]).position()[1];
            // std::cout << "x: " << positions[i][0] << "\ty: " << positions[i][1] << std::endl;
        }

        return positions_ptr;
    }

    int* Manager::get_colors(void){

        int rows = this->n_particles, cols = 3;
        this->colors_ptr = new int[rows * cols];
        for(int i = 0; i < rows; ++i){
                colors_ptr[cols*i] = (this->substrate[i]).color[0];
                colors_ptr[cols*i+1] = (this->substrate[i]).color[1];
                colors_ptr[cols*i+2] = (this->substrate[i]).color[2];
         }
        
        return colors_ptr;
    }

    void Manager::free_positions(void){
        // for(int i = 0; i < this->n_particles; ++i){
        //     delete[] positions_ptr[i];
        // }
        delete[] positions_ptr;
        positions_ptr = NULL;
    }

    void Manager::free_colors(void){
        // for(int i = 0; i < this->n_particles; ++i){
        //     delete[] colors_ptr[i];

        // }
        delete[] colors_ptr;
        colors_ptr = NULL;
    }




    }



