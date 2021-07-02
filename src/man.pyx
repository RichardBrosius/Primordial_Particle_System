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


    def initialize(self, int n_particles, int seed):
        self.c_part.initialize(n_particles, seed)
        self.n_particles = n_particles

    def sense(self):
        self.c_part.sense()

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




 