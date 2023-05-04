#!/bin/sh
set -v
rm -f ./cornellbox
g++ -o cornellbox LightBitmap.cpp LightTriangleIntersection.cpp LightRayTrace.cpp cornellbox.cpp ./src/* -O3 -std=c++11 -pthread -I include
echo CornellBox Compilation Finished!