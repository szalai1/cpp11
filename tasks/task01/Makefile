CC=g++
FLAGS=
BINARY=ratio
OBJECTS=main.o ratio.o
HEADERS=

$(BINARY): $(OBJECTS)
	$(CC) -g $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) $< -c -o $@

clean:
	rm -f *.o $(BINARY)

all: $(BINARY)
