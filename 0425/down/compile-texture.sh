#!/bin/sh
set -v
rm -f ./texture
g++ -o texture LightBitmap.cpp LightTriangleIntersection.cpp LightRayTrace.cpp LightTextureSphere.cpp texture.cpp liblight.a -O3 -std=c++11 -pthread -I include
echo Texture Compilation Finished!