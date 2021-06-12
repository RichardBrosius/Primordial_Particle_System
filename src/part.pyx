# distutils: language = c++

from Particle cimport Particle
from ctypes import *
from cpython cimport array

cdef class PyParticle:
    cdef Particle c_part


    # def __cinit__(self, int x0, int y0, int x1, int y1):
    #     self.c_part = Particle(x0, y0, x1, y1)
    #     self.c_part = Particle()


    #https://stackoverflow.com/questions/17014379/cython-cant-convert-python-object-to-double
    def __cinit__(self, int pid, array.array pos, double speed=1, double phi=0):
        cdef array.array pos_arr  = array.array('d', pos)
        
        self.c_part = Particle(pid, pos_arr.data.as_doubles, speed, phi )



    def move(self, double dt):
        self.c_part.move(dt)

    def orient(self, double dt):
        self.c_part.orient(dt)

    # def sense(self,  substrate):
    #     cdef double[2] n_count = self.c_rect.sense(substrate)
    #     return n_count