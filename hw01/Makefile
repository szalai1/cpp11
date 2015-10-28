CC=g++
FLAGS=-std=c++11 -Wall -Wdeprecated -g

main: string.o main.o test.o
	$(CC) $(FLAGS) $^ -o $@

string.o: string.cpp  string.h
	$(CC)  $(FLAGS) -c $< -o $@

main.o: main.cpp 
	$(CC)  $(FLAGS) -c $< -o $@

test.o: test.cpp test.h
	$(CC)  $(FLAGS) -c $< -o $@	

clean:
	rm *.o main
