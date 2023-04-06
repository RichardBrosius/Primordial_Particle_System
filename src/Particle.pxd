cdef extern from "Particle.cpp":
    pass

# Declare the class with cdef
cdef extern from "Particle.h" namespace "particles":
    cdef cppclass Particle:
        Particle() except +
        #Particle(int, int, int, int) except +


        Particle(int , double* , int, int, double, double) except +
        #~Particle()


        void move(double dt)
        void orient(double dt)
        double* get_position()

        int* sense(double** substrate)


