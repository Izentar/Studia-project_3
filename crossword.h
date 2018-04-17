#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <iostream>
#include <string>
#include <vector>

#include "node.h"
#include "word.h"

typedef unsigned int uint;

using namespace std;

template <typename Data>
class Crossword
{
    vector <Node*> knot;
    vector <Word*> words_x;
    vector <Word*> words_y;
    vector <uint> word_count;
    uint size_x, size_y;
    Data storage;

public:
    Crossword(Data&);
    ~Crossword();

    bool check();
    Data release();


};




#endif // CROSSWORD_H
