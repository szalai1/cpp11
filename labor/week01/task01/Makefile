CC=gcc
FLAGS=-std=c99 -Wall -Wdeprecated -pedantic -O2 -g 
BINARY=proba
OBJECTS=proba.o
HEADERS=

$(BINARY): $(OBJECTS)
	$(CC) -g $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) $< -c -o $@

clean:
	rm -f *.o $(BINARY)

all: $(BINARY)
