#!/bin/sh
rm -f ./bitmap
g++ -o bitmap LightBitmap.cpp bitmap.cpp liblight.a -O3 -std=c++11 -pthread -I include
echo Bitmap Compilation Finished!