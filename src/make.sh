#!/bin/bash

rm -rf build
python setup.py build_ext --inplace
