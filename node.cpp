#ifndef NODE_CPP
#define NODE_CPP

#include "node.h"
#define VOID '_'

using namespace std;

Node::Node(const uint& x, const uint& y)
:pos_x(x), pos_y(y), kar(VOID) {};

Node::~Node() {}

char Node::get_kar() const
{
    /*#ifdef DEBUG
    cout << "Taking in Node char " << kar << endl;
    #endif // DEBUG*/
    return kar;
}

uint Node::get_pos_x() const
{
    /*#ifdef DEBUG
    cout << "Taking in Node pos_x " << pos_x << endl;
    #endif // DEBUG*/
    return pos_x;
}

uint Node::get_pos_y() const
{
    /*#ifdef DEBUG
    cout << "Taking in Node pos_y " << pos_y << endl;
    #endif // DEBUG*/
    return pos_y;
}

void Node::change_kar(const char& new_char)
{
    if(new_char==kar)
    {
        return;
    }
    #ifdef DEBUG
    cout << "Changed kar in Node from " << kar;
    #endif // DEBUG
    kar=new_char;
    #ifdef DEBUG
    cout << " to " << kar << endl;
    #endif // DEBUG
}

void Node::push_back(Word* name)
{
    word_stack.push_back(name);
}

Word* Node::operator[] (const uint& index)
{
    if(index>word_stack.size())
    {
        #ifdef DEBUG
        clog << "Node::operator[]: out of index" << endl;
        #endif // DEBUG
        return nullptr;
    }

    return word_stack[index];
}

uint Node::size()
{
    return word_stack.size();
}

#endif // NODE_CPP
