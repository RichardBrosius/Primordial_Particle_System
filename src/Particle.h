#ifndef PARTICLE_H
#define PARTICLE_H

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
            int n_left;
            int n_right;
            double alpha;
            double beta;
            double domain;
            double* pos;
            double* color;

            int x0, x1, y0, y1;


            void move(double dt);
            void orient(double dt);
            //int* sense(double** substrate);


    };
}

#endif