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

crossword.o: crossword.cpp crossword.h
	$(CC) $(KONF) -c crossword.cpp crossword.h

data_stock.o: data_stock.cpp data_stock.h
	$(CC) $(KONF) -c data_stock.cpp data_stock.h

node.o: node.cpp node.h
	$(CC) $(KONF) -c node.cpp node.h

word.o: word.cpp word.h
	$(CC) $(KONF) -c word.cpp word.h

clean:
	rm -rf *o project1.out
