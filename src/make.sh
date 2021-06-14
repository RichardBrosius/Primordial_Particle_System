#!/bin/bash


rm part.cpython-36m-x86_64-linux-gnu.so man.cpython-36m-x86_64-linux-gnu.so
rm -rf build
python setup.py build_ext --inplace
