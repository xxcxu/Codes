#!/bin/sh
set -v
rm -f ./panorama
g++ -o panorama LightBitmap.cpp LightTriangleIntersection.cpp LightRayTrace.cpp LightCameraPanorama.cpp panorama.cpp liblight.a -O3 -std=c++11 -pthread -I include
echo Panorama Compilation Finished!