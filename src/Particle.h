#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>

namespace particles {
    class Particle {
        public:

            Particle();
            Particle(int pid, double* pos, double speed, double phi);
            //Particle(int x0, int y0, int x1, int y1);
            ~Particle();

            //double* pos = new double[2];
            double phi;
            double speed;
            int pid;
            //int* color = new int[3];
            int n_left_5;
            int n_right_5;
            int n_left_13;
            int n_right_13;

            double alpha;
            double beta;
            double domain;
            double* pos;
            double* color;

            int x0, x1, y0, y1;
            std::string color_category;

            void move(double dt);
            double* get_position();
            double* get_color();
            std::string get_color_category();

            void orient(double dt);
            void sense(double ** substrate, int num_particles);


    };
}

#endif