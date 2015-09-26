BINARY = main
OBJECTS = main.o
HEADERS = 

CC = gcc
CXX=g++
CXXFLAGS=-std=c++11
CFLAGS = -std=c11 -O0 -Wall -Wdeprecated -pedantic -g
LDFLAGS = -g

.PHONY: all clean

all: $(BINARY)

clean:
	rm -f $(BINARY) $(OBJECTS)

$(BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.c $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
