#!/usr/bin/env python3

from distutils.core import setup
#from setuptools import setup
from Cython.Build import cythonize

setup(
      name = "ppsapp",
      ext_modules = cythonize("part.pyx")              # our Cython source
      )
