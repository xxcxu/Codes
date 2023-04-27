#!/bin/sh
set -v
g++ -o triangle LightBitmap.cpp LightTriangleIntersection.cpp triangle.cpp liblight.a -O3 -std=c++11 -pthread -I include

echo Triangle Compilation Finished!