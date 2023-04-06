#include "Manager.h"
// https://stackoverflow.com/questions/13026523/undefined-symbol-error-importing-cython-module

// Must be added when used in cython
#include "Particle.cpp"
#include "Sthread.cpp"


#include "Sthread.h"
#include <stdlib.h>
#include <thread>
#include <vector>
#include<math.h>
#include<string>
#include <iostream>



namespace particles {

    class Particle;



    Manager::Manager(){
        std::vector<double> gpd[10]; // Green Particle Density
    }

    Manager::Manager(int x_size, int y_size){
        std::vector<double> gpd[10]; // Green Particle Density
        this->x_size = x_size;
        this->y_size = y_size;

    }

    Manager::~Manager(){
        // delete[] this->substrate;

    }

    void Manager::initialize(int n_particles, int seed){


        int MAX_PARTICLES = 10000;

        this->n_particles = n_particles;
        this->substrate = new Particle[MAX_PARTICLES];
        double* p1_pos;

        srand(seed);

        for(int i = 0; i < n_particles; i++){
            p1_pos = new double[2];
            p1_pos[0] = (rand() % this->x_size) / 1;
            p1_pos[1] = (rand() % this->y_size) / 1;
            Particle* p1 = new Particle(i, p1_pos, x_size, y_size, .67, rand() % 360);

            this->substrate[i] = *p1;

        }

    }



    void Manager::create_particles(int n_particles, int x, int y, int x_size, int y_size){

        int n_particles_old = this->n_particles;
        this->n_particles += n_particles;
        double* p1_pos;

        for(int i = n_particles_old - 1; i < this->n_particles; i++){
            p1_pos = new double[2];
            p1_pos[0] = x + (rand() % x_size) / 1;
            p1_pos[1] = y + (rand() % y_size) / 1;

            Particle* p1 = new Particle(i, p1_pos, this->x_size, this->y_size, .67, rand() % 360);
            //std::cout << "New Particle ID is " << std::endl;
            //std::cout << p1->pid << std::endl;
            this->substrate[i] = *p1;

        }



    }


    int Manager::regulate(int t, double target_density){

        // Calculate density
        double* pos;
        std::string color;
        int inbounds_particle_count = 0;
        x_size = this->x_size;
        y_size = this->y_size;

        for(int i = 0; i < this->n_particles; ++i)
        {
            pos = (this->substrate[i]).get_position();
            color = (this->substrate[i]).get_color_category();

            if( pos[0] >= 0 and pos[0] <= x_size and pos[1] >= 0 and pos[1] <= y_size) // and color == "Green")
            //if( color == "Green")
            {++inbounds_particle_count;}
        }

        // Since the area of the inbounds region remains constant it is sufficient to just track the number of particles
        double density = static_cast<double>(inbounds_particle_count) / static_cast<double>( x_size * y_size);
        (this->gpd)->push_back(density);

        if(this->gpd->size() > 10){
            this->gpd->erase(this->gpd->begin());
        }

        // Calculate the average of the last 10 iterations
        double accumulated_density = 0;
        for( auto it = this->gpd->begin(); it != this->gpd->end(); ++it)
        {
            accumulated_density += *it;
        }

        double density_ma = accumulated_density / 10.0;
        int particles_to_add = 0;


        if( t % 100 ==  0 ) 
        {
            std::cout << density_ma << " " << this->n_particles << std::endl;

        }
 
        if( density_ma < target_density)
        {
            double delta = abs(density_ma - target_density) +  t * (target_density - density_ma ) ;
            particles_to_add = static_cast<int> (delta * (this->n_particles)) / 3;
            std::cout << density_ma << " " << delta << " " << this->n_particles << " " << particles_to_add << std::endl;

        }


        return particles_to_add;

    }

    void Manager::sense(int NUM_CORES = 1){


        
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
            positions_ptr[cols*i] = (this->substrate[i]).get_position()[0];
            positions_ptr[cols*i+1] = (this->substrate[i]).get_position()[1];
        }

        return positions_ptr;
    }

    int* Manager::get_colors(void){

        int rows = this->n_particles, cols = 3;
        this->colors_ptr = new int[rows * cols];
        double* color;

        for(int i = 0; i < rows; ++i){
                color = (this->substrate[i]).get_color();
                colors_ptr[cols*i] = color[0];
                colors_ptr[cols*i+1] = color[1];
                colors_ptr[cols*i+2] = color[2];
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




    int* Manager::count_types(void){


        int* counts = new int[5];

        counts[0] = 0;
        counts[1] = 0;
        counts[2] = 0;
        counts[3] = 0;
        counts[4] = 0;

        std::string category;

        int rows = this->n_particles;

        for(int i=0; i < rows; ++i)
        {
            category = (this->substrate[i]).get_color_category();
            //Spore
            if( category == "Magenta")
            {++(counts[0]);}
            //Cells 
            else if( category == "Blue" )
            {++(counts[1]);}
            //Yellow
            else if( category == "Yellow")
            {++(counts[2]);}
            //Pre Spores 
            else if( category == "Brown" )
            {++(counts[3]);}
            //Nutrients
            else if(category == "Green")
            {++(counts[4]);}

        }

        return counts;

    }   
    
}
