SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))

.PHONY: all clean

all: liblight.a

liblight.a: $(OBJECTS)
	ar cr $@ $^

%.o: %.cpp
	g++ -c $^ -O2 -std=c++11 -o $@ -Iinclude -fno-common

clean:
	rm -rf $(OBJECTS) liblight.a
