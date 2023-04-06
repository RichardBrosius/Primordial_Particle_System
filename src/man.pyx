# distutils: language = c++

from Manager cimport Manager
from ctypes import *
import numpy as np
from libc.stdlib cimport free
from cython.view cimport array
import copy

cdef class PyManager:
    cdef Manager c_part
    cdef int n_particles


    def __cinit__(self):
        self.c_part = Manager()

    def __cinit__(self, int x_size, int y_size):
        self.c_part = Manager(x_size, y_size)


    def initialize(self, int n_particles, int seed):
        self.c_part.initialize(n_particles, seed)
        self.n_particles = n_particles

    def sense(self, int NUM_CORES = 1):
        self.c_part.sense(NUM_CORES)

    def move(self, double dt):
        self.c_part.move(dt)

    def orient(self, double dt):
        self.c_part.orient(dt)

    def getPositions(self):

        cdef double* positions_ptr = self.c_part.get_positions()
        # cdef double** positions_ptr = self.c_part.get_positions()
        #cdef double[:,:] positions_ptr = self.c_part.get_positions()


        positions = np.zeros((self.c_part.n_particles,2),dtype=float)
        cdef int cols = 2
        for i in range(0, self.c_part.n_particles):
            positions[i][0] = positions_ptr[i*cols]
            positions[i][1] = positions_ptr[i*cols + 1]

        # self.c_part.free_positions()

        # for i in range(0,self.c_part.n_particles):
        #     free(positions_ptr[i])
        #     positions_ptr[i] = NULL
        #np.reshape(positions,(self.c_part.n_particles,2),order='C')
        #positions_copy = copy.deepcopy(positions)
        free(positions_ptr)
        
        

        return positions


    def getColors(self):

        cdef int* colors_ptr = self.c_part.get_colors()
        # cdef int** colors_ptr = self.c_part.get_colors()

        colors = np.zeros((self.c_part.n_particles,3), dtype=int)
        cdef int cols = 3
        for i in range(0, self.c_part.n_particles):
            colors[i][0] = colors_ptr[i*cols]
            colors[i][1] = colors_ptr[i*cols + 1]
            colors[i][2] = colors_ptr[i*cols + 2]
    
        #self.c_part.free_colors()
        #numpy.reshape(colors,(self.c_part.n_particles,2),order='C')

        # colors_copy = copy.deepcopy(colors)
        free(colors_ptr)
        # for i in range(0,self.c_part.n_particles):
        #     free(colors_ptr[i])
        #     colors_ptr[i] = NULL


        return colors


    def regulate(self, int t,  double target_density):
        cdef int particles_to_add = self.c_part.regulate(t, target_density)
        return particles_to_add


    def create_particles(self, int n_particle, int x, int y, int x_size, int y_size):
        self.c_part.create_particles(n_particle, x, y, x_size, y_size)
    
    def count_types(self):
        cdef int* types_ptr = self.c_part.count_types()

        types = []
        types.append(types_ptr[0])
        types.append(types_ptr[1])
        types.append(types_ptr[2])
        types.append(types_ptr[3])
        types.append(types_ptr[4])


        free(types_ptr)


        return types