#include "Particle.h"
#include "math.h"
#include <iostream>
#include <string>

namespace particles {

    // Default constructor
    Particle::Particle () {
        this->color_category = 'U';

    }


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

        this->n_left_5 = 0;
        this->n_right_5 = 0;
        this->n_left_13 = 0;
        this->n_right_13 = 0;

        this->alpha = 180;
        this->beta = 17;
        this->domain = 5;

    }

    Particle::~Particle() {

        delete[] this->color;
        delete[] this->pos;
    }

    void Particle::move(double dt){
        this->pos[0] += cos(this->phi * M_PI / 180) * dt;
        this->pos[1] += sin(this->phi * M_PI / 180) * dt;

        // https://torstencurdt.com/tech/posts/modulo-of-negative-numbers/
        this->pos[0] = fmod(fmod(this->pos[0], 250) + 250 , 250);
        this->pos[1] = fmod(fmod(this->pos[1], 250) + 250,  250);

        if( this->pos[0] > 250.0 or this->pos[0] < 0)
        {
            std::cout << this->pos[0] << ',' << this->pos[1] << std::endl;
        }

    }

    void Particle::orient(double dt){

        int sign_n = ((this->n_right_5 - this->n_left_5) > 0 ) - ((this->n_right_5 - this->n_left_5) < 0 );
        double dphi_dt = this->alpha + this->beta * (this->n_right_5 + this->n_left_5) * sign_n;
        this->phi += dphi_dt * dt; 
    }


    double* Particle::get_color(void){
        return this->color;

    }

    std::string Particle::get_color_category(void)
    {
        return this->color_category;
    }

    double* Particle::get_position(void){
        return this->pos;
    }

   void Particle::sense(double** substrate, int num_particles){


       int r = 0;
       int l = 0;
       int i = 0;
       int n_13 = 0;

        double bx = this->pos[0] + this->domain * cos(this->phi * M_PI / 180);
        double by = this->pos[1] + this->domain * sin(this->phi * M_PI / 180);

        double ax = this->pos[0];
        double ay = this->pos[1];


        double x = 0.0;
        double y = 0.0;
        double cp = 0.0;
        int side = 0;
        double dx = 0.0;
        double dy = 0.0;
        double distance = 0.0;
        


       for(i=0; i < num_particles; i++)
       {

           x = substrate[i][0];
           y = substrate[i][1];

           cp = (bx-ax)*(y-ay) - (by-ay)*(x-ax);
           side = (cp > 0) - (cp < 0);

           dx = ax - x;
           dy = ay - y;
           
           distance = sqrt( pow(dx, 2) + pow(dy, 2) );

           if( side == 1 and distance <= this->domain )
           { r += 1;}
           else if ( side == -1 and distance <= this->domain)
           { l += 1;}

           if( distance < 1.3)
           {
               n_13++;
           }


       }

        this->n_right_5 = r;
        this->n_left_5 = l;
        int n_5 = l + r;


        int scale = 1;


        if( 15 * scale < n_5 and n_5 <= 35 * scale){ 
            // Blue
            this->color[0] = 0;
            this->color[1] = 0;
            this->color[2] = 255;
            this->color_category = "Blue";
        }
        else if( 35 * scale < n_5){ 
            // Yellow
            this->color[0] = 255;
            this->color[1] = 255;
            this->color[2] = 0;
            this->color_category = "Yellow";
        }

        else if( 13 * scale <= n_5 and n_5 <= 15 * scale){ 
            // Brown
            this->color[0] = 165;
            this->color[1] = 42;
            this->color[2] = 42;
            this->color_category = "Brown";
        }

        else if(n_13 > 15)
        {
            // Magenta
            this->color[0] = 255;
            this->color[1] = 0;
            this->color[2] = 255;
            this->color_category = "Magenta";
        }

        else{
            // Green
            this->color[0] = 0;
            this->color[1] = 255;
            this->color[2] = 0;
            this->color_category = "Green";
        }

   }




}