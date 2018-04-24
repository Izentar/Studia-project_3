#ifndef CROSSWORD_CPP
#define CROSSWORD_CPP

#include "crossword.h"

/*
using namespace std;

template <typename Data>
bool Crossword<Data>::shaping_words_x(Data& board)
{
    Word* tmp_word=nullptr;
    uint count=0;
    bool if_wrong=true;

    for(uint i=0; i<board.size_y(); i++)        // find in OX
    {
        for(uint j=1; j<board.size_x(); j++)
        {
            if(board.get_char(j, i)==board.get_master())
            {
                if(board.get_master()==board.get_char(j-1, i))
                {
                    if(tmp_word!=nullptr)
                    {
                        count++;
                    }
                    else
                    {
                        tmp_word=new Word(j, i);
                        if_wrong=false;
                        count+=2;
                    }
                }
            }
            else
            {
                if(count!=0)
                {
                    tmp_word->resize(count);
                    count=0;
                }
                if(tmp_word!=nullptr)
                {
                    words_x.push_back(tmp_word);
                    tmp_word=nullptr;
                }
            }
        }
        if(count!=0&&count!=1)
        {
            tmp_word->resize(count);
        }
        count=0;
        if(tmp_word!=nullptr)
        {
            words_x.push_back(tmp_word);
            tmp_word=nullptr;
        }
    }
    if(if_wrong)
    {
        return true;
    }

    return false;
}

template <typename Data>
bool Crossword<Data>::shaping_words_y(Data& board)
{
    Word* tmp_word=nullptr;
    uint count=0;
    bool if_wrong=true;

    for(uint i=0; i<board.size_x(); i++)         // find in OY
    {
        for(uint j=1; j<board.size_y(); j++)
        {
            if(board.get_char(i, j)==board.get_master())
            {
                if(board.get_master()==board.get_char(i, j-1))
                {
                    if(tmp_word!=nullptr)
                    {
                        count++;
                    }
                    else
                    {
                        tmp_word=new Word(i, j);
                        if_wrong=false;
                        count+=2;
                    }
                }
            }
            else
            {
                if(count!=0)
                {
                    tmp_word->resize(count);
                    count=0;
                }
                if(tmp_word!=nullptr)
                {
                    words_y.push_back(tmp_word);
                    tmp_word=nullptr;
                }
            }
        }
        if(count!=0&&count!=1)
        {
            tmp_word->resize(count);
        }
        count=0;
        if(tmp_word!=nullptr)
        {
            words_y.push_back(tmp_word);
            tmp_word=nullptr;
        }

    }

    return false;
}

template <typename Data>
void Crossword<Data>::shaping_nodes(Data& board)
{

    for(int i=0; i<board.size_y(); i++)         // find Nodes
    {
        for (int j=0; j<board.size_x(); j++)
        {
            if(board.get_char(j, i)==board.get_master())
            {
                if(i<board.size_y()-1&&j<board.size_x()-1&&board.get_master()==board.get_char(j, i+1)&&board.get_master()==board.get_char(j+1, i))
                {
                    knot.push_back(new Node(j, i));
                }
                else
                if(i>=1&&j<board.size_x()-1&&board.get_master()==board.get_char(j, i-1)&&board.get_master()==board.get_char(j+1, i))
                {
                    knot.push_back(new Node(j, i));
                }
                else
                if(i>=1&&j>=1&&board.get_master()==board.get_char(j, i-1)&&board.get_master()==board.get_char(j-1, i))
                {
                    knot.push_back(new Node(j, i));
                }
                else
                if(i<board.size_y()-1&&j>=1&&board.get_master()==board.get_char(j, i+1)&&board.get_master()==board.get_char(j-1, i))
                {
                    knot.push_back(new Node(j, i));
                }
            }
        }
    }
}

template <typename Data>
Crossword<Data>::Crossword(Data& board)
{
    uint max_x=0;
    uint max_y=0;


    if(shaping_words_x(board)||shaping_words_y(board))
    {
        clog << "no word was found in the crossword puzzle" << endl;
    }
    else
    {
        shaping_nodes(board);
    }

    #ifdef DEBUG
    cout << "Created Crossword" << endl;
    #endif
}

template <typename Data>
Crossword<Data>::~Crossword()
{
    for(uint i=0; i<knot.size(); i++)
    {
        delete knot[i];
    }
    for(uint i=0; i<words_x.size(); i++)
    {
        delete words_x[i];
    }
    for(uint i=0; i<words_y.size(); i++)
    {
        delete words_y[i];
    }
    #ifdef DEBUG
    cout << "Deleted Crossword" << endl;
    #endif
}

template <typename Data>
Crossword<Data>::Crossword(Crossword& primary)        // dokończyć
{
    for (uint i=0; i<primary.knot.size(); i++)
    {
        knot.push_back(new Node(primary.knot[i]->get_pos_x(), primary.knot[i]->get_pos_y()));
        knot[i]->change_kar(primary.knot[i]->get_kar());
    }
    for (uint i=0; i<primary.words_x.size(); i++)
    {
        words_x.push_back(new Word(primary.words_x[i]->get_pos_x(), primary.words_x[i]->get_pos_y()));
        words_x[i]->change_name(primary.words_x[i]->get_name());
    }
    for (uint i=0; i<primary.words_y.size(); i++)
    {
        words_y.push_back(new Word(primary.words_y[i]->get_pos_x(), primary.words_y[i]->get_pos_y()));
        words_y[i]->change_name(primary.words_y[i]->get_name());
    }

    #ifdef DEBUG
    cout << "Copied crossword" << endl;
    #endif // DEBUG
}

template <typename Data>
void Crossword<Data>::write_in_console()
{
    cout << endl << "Nodes:" << endl;
    for (uint i=0; i<knot.size(); i++)
    {
        cout << i << ". " << knot[i]->get_pos_x() << " " << knot[i]->get_pos_y() << " " << knot[i]->get_kar() << endl;
    }
    cout << endl << "Words_x" << endl;
    for (uint i=0; i<knot.size(); i++)
    {
        cout << i << ". " << words_x[i]->get_pos_x() << " " << words_x[i]->get_pos_y() << " " << words_x[i]->get_name() << endl;
    }
    cout << endl << "Words_y" << endl;
    for (uint i=0; i<knot.size(); i++)
    {
        cout << i << ". " << words_y[i]->get_pos_x() << " " << words_y[i]->get_pos_y() << " " << words_y[i]->get_name() << endl;
    }
}

*/
#endif // CROSSWORD_CPP
