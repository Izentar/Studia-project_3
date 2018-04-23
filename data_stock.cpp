#ifndef DATA_STOCK_CPP
#define DATA_STOCK_CPP

#include "data_stock.h"

#define VOID '_'

using namespace std;

Board_stock::Board_stock(): max_size_x(0), max_size_y(0), master(VOID) {}

Board_stock::~Board_stock() {}

void resize(string& tmp, const uint& number, const char& character)
{
    stringstream ss;
    for (uint i=0; i<number; i++)
    {
        ss<<character;
    }
    tmp=tmp+ss.str();
}

bool Board_stock::read_console()
{
    string tmp;
    char filling;
    uint numb_tmp;

    cout << "master ";
    cin.get(master);
    cin.ignore(128, '\n');
    if(master==VOID)
    {
        return true;
    }


    cout << "filling: ";
    cin.get(filling);
    cin.ignore(128, '\n');
    if(filling==master||filling==VOID)
    {
        return true;
    }

    cout << "size y: ";
    cin >> max_size_y;
    cin.ignore(128, '\n');
    for (uint i=0; i<max_size_y; i++)       //loading
    {
        getline(cin, tmp, '\n');
        for (uint j=0; j<tmp.size(); j++)
        {
            if(tmp[j]!=master||tmp[j]!=filling)
            {
                clog << "Read wrong char: read_file_data" << endl;
                return true;
            }
        }
        if(max_size_x<tmp.size()) max_size_x=tmp.size();
        Data_stock.push_back(tmp);
    }

    for (uint i=0; i<max_size_y; i++)       // filling
    {
        resize(Data_stock[i], max_size_x-Data_stock[i].size(), filling);
    }

    cout << endl << "number of words: ";
    cin >> numb_tmp;
    for (uint i=0; i<numb_tmp; i++)
    {
        cin >> tmp;
        Word_stock.push_back(tmp);
    }

    return false;
}

bool read_from_file(const string& name_file, stringstream& ss)
{
    fstream file;
    file.open(name_file, ios::in);
    if(file)
    {
        ss << file.rdbuf();
        #ifdef DEBUG
        cout << "File: " << endl << ss.str() << endl;
        #endif // DEBUG
        file.close();
        return false;
    }
    else
    {
        return true;
    }
}

bool Board_stock::read_file_data(const string& name_file)
{
    string line;
    char filling;
    stringstream ss;

    read_from_file(name_file, ss);
    if(name_file[name_file.size()-1]=='b'&&name_file[name_file.size()-2]=='.')
    {
        ss >> master;
        #ifdef DEBUG
        if(master==VOID)
        {
            clog << "Unacceptable first char" << endl;
            return true;
        }
        #endif // DEBUG
        ss >> filling;
        #ifdef DEBUG
        if(filling==VOID||filling==master)
        {
            clog << "Unacceptable second char" << endl;
            return true;
        }
        #endif // DEBUG
        while(!ss.eof())
        {
            ss >> line;
            if(ss.tellg()!=-1)
            {
                #ifdef DEBUG
                for (uint i=0; i<line.size(); i++)
                {

                    if(!(line[i]==master||line[i]==filling||line[i]=='\n'))
                    {
                        clog << "Read wrong char: read_file_data: " << "'"<< line[i] << "'" << endl;
                        return true;
                    }
                }
                #endif // DEBUG

                if(max_size_x<line.size())
                {
                    max_size_x=line.size();
                }
                Data_stock.push_back(line);
            }
        }
        max_size_y=Data_stock.size();

        for (uint i=0; i<Data_stock.size(); i++)
        {
            ss.str("");
            for (uint j=Data_stock[i].size(); j<max_size_x; j++)
            {
                ss << filling;
            }
            resize(Data_stock[i], max_size_x-Data_stock[i].size(), filling);
        }

    }
    else
    {
        clog << "Unknown file" << endl;
        return true;
    }
    return false;
}

bool Board_stock::read_file_words(const string& name_file)
{
    string line;
    stringstream ss;

    read_from_file(name_file, ss);


    if(name_file[name_file.size()-1]=='w'&&name_file[name_file.size()-2]=='.')
    {
        while(!ss.eof())
        {
            ss >> line;
            if(ss.tellg()!=-1)
            {
                Word_stock.push_back(line);
            }
        }
    }
    else
    {
        clog << "Unknown file" << endl;
        return true;
    }

    return false;
}

uint Board_stock::size_y() const
{
    return max_size_y;
}

uint Board_stock::size_x() const
{
    return max_size_x;
}

char Board_stock::get_master() const
{
    return master;
}

char Board_stock::get_char(const uint& x, const uint& y) const
{
    if(x<max_size_x&&y<max_size_y)
    {
        return Data_stock[y][x];
    }
    else
    {
        clog << "Board_stock: get_char: there is not such a char" <<endl;
        return VOID;
    }
}

void Board_stock::write_in_console() const
{
    cout << endl << endl;
    for(uint i=0; i<Data_stock.size(); i++)
    {
        cout << Data_stock[i] << endl;
    }
    cout << endl;
    for (uint i=0; i<Word_stock.size(); i++)
    {
        cout << Word_stock[i] << endl;
    }
}

std::string* Board_stock::get_word(const uint& index)
{
    if(index<Word_stock.size())
    {
        return &Word_stock[index];
    }
    else
    {
        return &Word_stock[Word_stock.size()];
    }
}

uint Board_stock::words_size()
{
    return Word_stock.size();
}


#endif // DATA_STOCK_CPP
