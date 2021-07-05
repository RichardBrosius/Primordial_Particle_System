# distutils: language = c++

from Particle cimport Particle
from ctypes import *
from cpython cimport array
import numpy as np
cimport numpy as cnp

cdef class PyParticle:
    cdef Particle c_part


    #https://stackoverflow.com/questions/17014379/cython-cant-convert-python-object-to-double
    def __cinit__(self, int pid, array.array pos, double speed=1, double phi=0):
        cdef array.array pos_arr  = array.array('d', pos)
        
        self.c_part = Particle(pid, pos_arr.data.as_doubles, speed, phi )

    def move(self, double dt):
        self.c_part.move(dt)

    def orient(self, double dt):
        self.c_part.orient(dt)

    def position(self):
        cdef double[2] pos = self.c_part.get_position()
        return pos


