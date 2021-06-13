#include "Particle.h"
#include "math.h"
#include <iostream>

namespace particles {

    // Default constructor
    Particle::Particle () {}


    Particle::Particle (int pid, double* position, double speed, double phi) {


        this->pos = new double[2];
        this->pos[0] = position[0]; // x coord
        this->pos[1] = position[1]; // y coord

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

    void Particle::move(double dt){
        this->pos[0] += cos(this->phi * M_PI / 180) * dt;
        this->pos[1] += sin(this->phi * M_PI / 180) * dt;
    }

    void Particle::orient(double dt){

        int sign_n = ((this->n_right - this->n_left) > 0 ) - ((this->n_right - this->n_left) < 0 );
        double dphi_dt = this->alpha + this->beta * (this->n_right + this->n_left) * sign_n;
        this->phi += dphi_dt * dt; 
    }

    double* Particle::position(void){
        return this->pos;
    }

   int* Particle::sense(double** substrate){

       int n_particles = sizeof(substrate) / sizeof(substrate[0]);

       int r = 0;
       int l = 0;
       int i = 0;

        double bx = this->pos[0] + this->domain * cos(this->phi * M_PI / 180);
        double by = this->pos[1] + this->domain * sin(this->phi * M_PI / 180);

        double ax = this->pos[0];
        double ay = this->pos[1];


       for(i=0; i < n_particles; i++)
       {

           double x = substrate[i][0];
           double y = substrate[i][1];

           //std::cout << printf("x: %f ,y: %f \n", x,y);

           std::cout << "x:" << x;
           std::cout << "\t y:" << y << std::endl;

           double cp = (bx-ax)*(y-ay) - (by-ay)*(x-ax);
           int side = (cp > 0) - (cp < 0);

           double dx = ax - x;
           double dy = ay - y;
           
           double distance = sqrt( pow(dx, 2) + pow(dy, 2) );

           if( side == 1 and distance <= this->domain )
           { r += 1;}
           else if ( side == -1 and distance <= this->domain)
           { l += 1;}

       }

        this->n_right = r;
        this->n_left = l;
        int n = l + r;

        int scale = 1;

        if( 3 * scale < n and n < 8 * scale){ 
            this->color[0] = 0;
            this->color[1] = 255;
            this->color[2] = 0;
        }
        else if( 8 * scale < n and n < 12 * scale){ 
            this->color[0] = 255;
            this->color[1] = 165;
            this->color[2] = 0;
        }
            else if( 12 * scale < n){ 
            this->color[0] = 255;
            this->color[1] = 0;
            this->color[2] = 0;
        }

        int* lr_counts = new int[2];
        lr_counts[0] = this->n_left;
        lr_counts[1] = this->n_right;
        
        return lr_counts;
       

   }




}