#ifndef DATA_STOCK_H
#define DATA_STOCK_H

#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int uint;

class Board_stock
{
    vector<vector<char>> Data;
    char master;


public:
    Board_stock();
    ~Board_stock();

    friend class crossword;

    bool read_file();
    bool read_console();

    uint size_y();
    uint size_x(uint y);
    char get_master();
    char get_char(uint X, uint Y);
};





#endif // DATA_STOCK_H
