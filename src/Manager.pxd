#from Particle cimport Particle


cdef extern from "Manager.cpp":
    pass

cdef extern from "Manager.h" namespace "particles":
    cdef cppclass Manager:
        Manager(int x_size, int y_size) except + 
        Manager() except + 
        # Particle* substrate
        int n_particles

        void initialize(int n_particles, int seed)
        void sense()
        void free_positions()
        void free_colors()
        void move(double dt)
        void orient(double dt)
        double* get_positions()
        int* get_colors()
        int regulate(int t, double target_density)
        void create_particles(int n_particles)