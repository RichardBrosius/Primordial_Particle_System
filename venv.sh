#/bin/bash

virtualenv venv 

if source venv/bin/activate;
then pip install PyOpenGL PyOpenGL_accelerate
     pip install pygame
     pip install numpy
     pip install cython
     pip install --upgrade cython
     pip install ipython
else echo Venv Activation Failed
fi
