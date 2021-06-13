cdef extern from "Particle.cpp":
    pass

# Declare the class with cdef
cdef extern from "Particle.h" namespace "particles":
    cdef cppclass Particle:
        Particle() except +
        #Particle(int, int, int, int) except +


        Particle(int , double* , double, double) except +
        #~Particle()


        void move(double dt)
        void orient(double dt)
        double* position()

        int* sense(double** substrate)


