#ifndef DATA_STOCK_H
#define DATA_STOCK_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>


typedef unsigned int uint;

class Board_stock
{
    uint max_size_x, max_size_y;
    char master;
    std::vector<std::string> Data_stock;
    std::vector<std::string> Word_stock;

public:
    Board_stock();
    ~Board_stock();

    // for users
    bool read_file_data(const std::string&);
    bool read_file_words(const std::string&);
    bool read_console();
    void write_in_console() const;
    // end

    // for program, must have
    uint size_y() const;
    uint size_x() const;
    char get_master() const;
    char get_char(const uint& x, const uint& y) const;
    std::string* get_word(const uint&);
    uint words_size();
    // end

    // used in program functions
    friend void resize(std::string&, const uint&, const char&);
    // end
};





#endif // DATA_STOCK_H
