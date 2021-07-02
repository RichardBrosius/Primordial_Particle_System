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


        // SThread t1 = SThread();

        // t1(this->substrate, this->n_particles, 0, 1000);

        std::thread th1(SThread(), this->substrate, this->n_particles, 0, 625);
        std::thread th2(SThread(), this->substrate, this->n_particles, 625, 1250);
        std::thread th3(SThread(), this->substrate, this->n_particles, 1250, 1875);
        std::thread th4(SThread(), this->substrate, this->n_particles, 1875, 2500);
        std::thread th5(SThread(), this->substrate, this->n_particles, 2500, 3125);
        std::thread th6(SThread(), this->substrate, this->n_particles, 3125, 3750);
        std::thread th7(SThread(), this->substrate, this->n_particles, 3750, 4375);
        std::thread th8(SThread(), this->substrate, this->n_particles, 4375, 5000);


        th1.join();
        th2.join();
        th3.join();
        th4.join();
        th5.join();
        th6.join();
        th7.join();
        th8.join();



        // double** positions = new double* [this->n_particles];
        // double* position = new double[2];
        // int* result = new int[2];

        // for(int i=0; i < n_particles; i++){
        //     positions[i] = new double[2];
        //     position = (this->substrate[i]).position();

        //     positions[i][0] = position[0];
        //     positions[i][1] = position[1];
        // }

        // for(int i=0; i < n_particles; i++){
        //     result = (this->substrate[i]).sense(positions, this->n_particles);
        //     //std::cout << result[0] << "," << result[1] << std::endl;
        // }
   

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



