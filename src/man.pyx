# distutils: language = c++

from Manager cimport Manager
from ctypes import *
import numpy as np

cdef class PyManager:
    cdef Manager c_part
    cdef int n_particles

    def __cinit__(self):
        self.c_part = Manager()


    def initialize(self, int n_particles):
        self.c_part.initialize(n_particles)
        self.n_particles = n_particles

    def sense(self):
        self.c_part.sense()

    def move(self, double dt):
        self.c_part.move(dt)

    def orient(self, double dt):
        self.c_part.orient(dt)

    def getPositions(self):
        cdef double** positions_ptr = self.c_part.get_positions()

        positions = np.zeros((self.c_part.n_particles,2))

        for i in range(0, self.c_part.n_particles):
            positions[i][0] = positions_ptr[i][0]
            positions[i][1] = positions_ptr[i][1]


        return positions




 