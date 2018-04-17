CC=g++
KONF=-std=c++11

RELEASE: KONF+= -O2
RELEASE: project2.out

DEBUG: KONF=-g -DDEBUG
DEBUG: project2.out

project2.out: main.o crossword.o
	$(CC) main.o crossword.o -o project2.out

main.o: main.cpp
	$(CC) $(KONF) -c main.cpp

crossword.o: crossword.cpp
	$(CC) $(KONF) -c crossword.cpp

clean:
	rm -rf *o project1.out
