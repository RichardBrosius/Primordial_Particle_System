#!/usr/bin/env python3

from distutils.core import setup
#from setuptools import setup
from Cython.Build import cythonize

#https://www.bookstack.cn/read/cython-3.0-en/fb8e904dbf5c241b.md
setup(
      name = "ppsapp",
      ext_modules = cythonize("*.pyx")              # our Cython source
      )
