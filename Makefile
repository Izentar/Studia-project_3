CC=g++
KONF=-std=c++11

RELEASE: KONF+= -O2
RELEASE: project2.out

DEBUG: KONF+=-g -DDEBUG
DEBUG: project2.out

project2.out: main.o crossword.o data_stock.o node.o word.o
	$(CC) main.o crossword.o data_stock.o node.o word.o -o project2.out

main.o: main.cpp
	$(CC) $(KONF) -c main.cpp

crossword.o: crossword.h crossword.cpp
	$(CC) $(KONF) -c crossword.cpp crossword.h

data_stock.o: data_stock.h data_stock.cpp
	$(CC) $(KONF) -c data_stock.cpp data_stock.h

node.o: node.h node.cpp
	$(CC) $(KONF) -c node.cpp node.h

word.o: word.h word.cpp
	$(CC) $(KONF) -c word.cpp word.h

clean:
	rm -rf *o project1.out
