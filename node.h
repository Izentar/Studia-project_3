#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int uint;

class Node
    {
        uint pos_x, pos_y;
        char kar;

    public:
        Node(const uint&, const uint&);
        ~Node();

        char get_kar();
        uint get_pos_x();
        uint get_pos_y();
        void change_kar(char);
    };


#endif // NODE_H
