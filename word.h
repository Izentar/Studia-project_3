#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <vector>
#include <sstream>


#include "node.h"

using namespace std;

typedef unsigned int uint;

class Node;

class Word
{
    uint pos_x, pos_y, pos;     // pos - x or y
    bool used;
    string word_stock;
    vector <Node*> word_nodes;
    //vector <bool> already_checked;

public:

    Word(const uint&, const uint&, const char&);
    ~Word();

    void resize(uint&);
    bool change_name(const string&);       // changes nodes too
    void erase();                          // erase word_stock by adding '_'
    bool connect_node(Node*);
    string get_name() const;
    char operator[] (const uint&) const;
    Node* operator% (const uint&) const;
    uint get_pos_x() const;
    uint get_pos_y() const;
    uint size() const;              // size of word_stock
    uint size_node() const;
    bool busy() const;                  // if used or not
    bool check_nodes(const string*);        // true if good
    /*uint size_bool() const;
    bool bool_check(const uint&) const;
    void bool_push_back(const bool&);
    void bool_erase();*/

};


#endif // WORD_H
