#ifndef CROSSWORD_CPP
#define CROSSWORD_CPP

#include "crossword.h"

using namespace std;

template <typename Data>
Crossword<Data>::find_x()
{

}


template <typename Data>
Crossword<Data>::Crossword(Data& board)
{
    uint max_x=0;
    uint max_y=0;
    Node* tmp_node=nullptr;
    Word* tmp_word=nullptr;

    for(int i=0; i<board.size_y(); i++)         // find in OX and Nodes
    {
        for(int j=0; j<board.size_x(i); j++)
        {
            if(board.get_char(j, i)==board.get_master())
            {
                if(j>=1&&board.get_master()==board.get_char(j-1, i))
                {
                    if(tmp_word!=nullptr)
                    {
                        tmp_word->push_back(board.get_master());
                    }
                    else
                    {
                        tmp_word=new Word*;
                        tmp_word->push_back(board.get_master());
                        tmp_word->push_back(board.get_master());
                    }
                }
            }
            else
            {
                tmp_word=nullptr;
            }
        }
        tmp_word=nullptr;
    }


    for(int i=0; i<max_x; i++)         // find in OY
    {
        for(int j=0; j<max_y; j++)
        {
            if(board.get_char(i, j)==board.get_master())
            {

            }
        }


    }

    for(int i=0; i<board.size_y(); i++)         // find Nodes
    {
        for (int j=0; j<board.size_x(i); j++)
        {
            if(board.get_char(0, i)==board.get_master())
            {
                if(i>=1&&j>=1&&board.get_master()==board.get_char(j, i-1)&&board.get_master()==board.get_char(j-1, i))
                {

                }
                if(i>=1&&j>=1&&board.get_master()==board.get_char(j, i-1)&&board.get_master()==board.get_char(j-1, i))
                {

                }
            }
        }

    }



    #ifdef DEBUG
    cout << "Created Crossword" << endl;
    #endif
}
template <typename Data>
Crossword<Data>::~Crossword()
{
    #ifdef DEBUG
    cout << "Deleted Crossword" << endl;
    #endif
}






#endif // CROSSWORD_CPP
