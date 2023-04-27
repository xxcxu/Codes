#!/bin/sh
rm -f ./balls
g++ -o balls LightBitmap.cpp LightTriangleIntersection.cpp LightRayTrace.cpp balls.cpp liblight.a -O3 -std=c++11 -pthread -I include
echo Balls Compilation Finished!