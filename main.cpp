/*
notka:
nie uzywac znaku '_' w plikach z danymi bo jest zarezerwowany

!!!!!!! bool Word::change_name(const string& name)

1. jedyny warunek na pomyślne zakończenie, to to, że word jest zajęty
2. jedyny warunek na niepowodzenie, to brak zarezerwowania słowa

!! jaki warunek na zakonczenie rekurencji???
*/

#include <iostream>
#include <fstream>
#include "crossword.h"
#include "data_stock.h"
//#define DEBUG

using namespace std;

int main(int ac, char* av[])
{
    #ifdef DEBUG
    std::ofstream out("ERRORS.txt");
    auto old_rdbuf = std::clog.rdbuf();
    std::clog.rdbuf(out.rdbuf());
    #endif // DEBUG

    cout << "Hello world!" << endl;

    Board_stock stock;
    //stock.read_console();

    for (int i=1; i<ac; i+=2)
    {
        if(stock.read_file_data(av[i])) clog << "Unable to open file" << endl;
        if(stock.read_file_words(av[i+1])) clog << "Unable to open file" << endl;
        //cout << av[i] << endl;
    }
    //stock.write_in_console();


    //stock.write_in_console();
    //cout << endl;
    Crossword <Board_stock> first(stock);
    //first.sort_words();
    //first.check_solution();



    Board_stock *new_stock;
    new_stock=first.release(' ');

    //first.write_in_console();

    if(new_stock!=nullptr)
    {
        new_stock->write_in_console();
    }
    else
    {
        cout << "Crossword cannot be created. Words and container shape does not fit." << endl;
    }

    delete new_stock;

    #ifdef DEBUG
    std::clog.rdbuf(old_rdbuf);
    out.close();
    #endif // DEBUG

    return 0;
}
