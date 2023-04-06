#!/bin/bash

virtualenv venv --python=/usr/bin/python3

if source venv/bin/activate
then echo activated!

     #Program Libraries
     pip install PyOpenGL PyOpenGL_accelerate
     pip install pygame
     pip install numpy
     pip install cython
     pip install --upgrade cython
     pip install ipython

     #Jupyter notebook modules
     pip install matplotlib
     pip install pandas
     pip install statsmodels

else echo Venv Activation Failed
fi
