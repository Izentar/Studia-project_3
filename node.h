#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>

#include "word.h"

typedef unsigned int uint;

class Word;

class Node
    {
        uint pos_x, pos_y;
        char kar;
        std::vector <Word*> word_stack;

    public:
        Node(const uint&, const uint&);
        ~Node();

        char get_kar() const;
        uint get_pos_x() const;
        uint get_pos_y() const;
        void change_kar(const char&);
        void push_back(Word*);
        uint size();
        Word* operator[] (const uint&);

    };


#endif // NODE_H
