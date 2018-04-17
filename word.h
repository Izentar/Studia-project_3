#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int uint;


class Word
    {
        vector <char> word_stock;
        uint pos_x, pos_y;

    public:
        Word(const uint, const uint);
        ~Word();

        void push_back(const char&);
        void push_name(string);
        void push_name(const char&);
        char operator[] (int);
        uint begin_x();
        uint begin_y();
    };


#endif // WORD_H
