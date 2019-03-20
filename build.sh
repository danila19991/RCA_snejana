#!/bin/bash
rm -r build
mkdir build
cd build
qmake ../RCA1_0.pro
make

