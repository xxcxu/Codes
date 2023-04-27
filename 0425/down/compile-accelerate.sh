#!/bin/sh
set -v
rm -f ./accelerate
g++ -o accelerate LightMeshAccelerate.cpp LightBitmap.cpp LightTriangleIntersection.cpp LightPathTrace.cpp accelerate.cpp liblight.a -O3 -std=c++11 -pthread -I include
echo Accelerate Compilation Finished!