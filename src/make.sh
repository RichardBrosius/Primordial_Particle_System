#!/bin/bash


rm man.cpython-39-x86_64-linux-gnu.so
rm part.cpython-39-x86_64-linux-gnu.so 
rm -rf build
python setup.py build_ext --inplace
