#!/bin/sh
rm -f ./pathtracing
g++ -o pathtracing LightBitmap.cpp LightTriangleIntersection.cpp LightPathTrace.cpp pathtracing.cpp liblight.a -O3 -std=c++11 -pthread -I include
echo PathTracing Compilation Finished!