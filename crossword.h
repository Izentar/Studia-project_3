#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "word.h"

#define VOID '_'

typedef unsigned int uint;

template <typename Data>
class Crossword
{
    std::vector <Node*> knot;       // nodes all
    std::vector <Word*> words_x;
    std::vector <Word*> words_y;
    std::vector <std::string*> main_words;  // specific words from Data
    std::vector <uint> word_count;          // how many words by size
    std::vector <Word*> word_stack;         // all words from words_x and words_y
    Data storage;
    uint max_x, max_y;

    bool shaping_words_x(Data&);
    bool shaping_words_y(Data&);
    void shaping_nodes(Data&);
    void connecting();
    void counting_words(Data&);
    bool recursion_word(bool if_free[], std::vector<Word*>& , std::vector<uint>& , Word* , uint );

public:

    Crossword(Data&);
    ~Crossword();
    Crossword(Crossword&);

    void write_in_console();
    bool check_words();
    void sort_words();
    bool check_solution();
    Data* release(const char&);

};

template<typename Data>
void Crossword<Data>::counting_words(Data& board)
{
    string tmp;
    uint max_size_word=0;

    for (uint i=0; i<board.words_size(); i++)
    {
        tmp=*board.get_word(i);
        if(max_size_word<tmp.size()+1)
        {
            max_size_word=tmp.size()+1;
        }
    }

    word_count.resize(max_size_word);

    for (uint i=0; i<max_size_word; i++)
    {
        word_count[i]=0;
    }

    for (uint i=0; i<board.words_size(); i++)
    {
        tmp=*board.get_word(i);
        word_count[tmp.size()]++;
    }
}

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
                        /*#ifdef DEBUG
                        cout << "count " << count << endl;
                        #endif // DEBUG*/
                    }
                    else
                    {
                        tmp_word=new Word(j-1, i, 'x');
                        if_wrong=false;
                        count+=2;
                        #ifdef DEBUG
                        cout << "Created Word in Crossword_x " << count << endl;
                        #endif // DEBUG
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
                    #ifdef DEBUG
                    cout << "Added word in Crossword_x" << endl;
                    #endif // DEBUG
                    words_x.push_back(tmp_word);
                    tmp_word=nullptr;
                }
            }
        }
        if(count!=0&&count!=2)
        {
            tmp_word->resize(count);
        }
        count=0;
        if(tmp_word!=nullptr)
        {
            #ifdef DEBUG
            cout << "Added word in Crossword_x: new line" << endl;
            #endif // DEBUG
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
                        #ifdef DEBUG
                        cout << "count " << count << endl;
                        #endif // DEBUG
                    }
                    else
                    {
                        #ifdef DEBUG
                        cout << "Created word in Crossword_y " << count << endl;
                        #endif // DEBUG
                        tmp_word=new Word(i, j-1, 'y');
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
                    #ifdef DEBUG
                    cout << "Added word in Crossword_y" << endl;
                    #endif // DEBUG
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
            #ifdef DEBUG
            cout << "Added word in Crossword_y: new line" << endl;
            #endif // DEBUG
            words_y.push_back(tmp_word);
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
void Crossword<Data>::connecting()          // !!!!!!!!!! OK OK
{
    for (uint a=0; a<words_x.size(); a++)
    {
        for (uint i=0; i<knot.size(); i++)
        {
            if(knot[i]->get_pos_x()>=words_x[a]->get_pos_x()&&knot[i]->get_pos_x()<words_x[a]->get_pos_x()+words_x[a]->size()&&knot[i]->get_pos_y()==words_x[a]->get_pos_y())
            {
                words_x[a]->connect_node(knot[i]);
                knot[i]->push_back(words_x[a]);
                #ifdef DEBUG
                cout << "connected node to word_x and word to node: x " << words_x[a]->get_pos_x() << " y "  << words_x[a]->get_pos_y() << " node x " << knot[i]->get_pos_x() << " y " << knot[i]->get_pos_y() << endl;
                #endif // DEBUG
            }
        }
    }

    for (uint a=0; a<words_y.size(); a++)
    {
        for (uint i=0; i<knot.size(); i++)
        {
            if(knot[i]->get_pos_y()>=words_y[a]->get_pos_y()&&knot[i]->get_pos_y()<words_y[a]->get_pos_y()+words_y[a]->size()&&knot[i]->get_pos_x()==words_y[a]->get_pos_x())
            {
                words_y[a]->connect_node(knot[i]);
                knot[i]->push_back(words_y[a]);
                #ifdef DEBUG
                cout << "connected node to word_y and word to node: x " << words_y[a]->get_pos_x() << " y "  << words_y[a]->get_pos_y() << " node x " << knot[i]->get_pos_x() << " y " << knot[i]->get_pos_y() << endl;
                #endif // DEBUG
            }
        }
    }

}

template <typename Data>
void Crossword<Data>::shaping_nodes(Data& board)
{
    for(uint i=0; i<board.size_y(); i++)         // find Nodes
    {
        for (uint j=0; j<board.size_x(); j++)
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
void Crossword<Data>::sort_words()
{
    Word* tmp=nullptr;
    string* tm;

    word_stack.clear();

    for (uint i=0; i<words_x.size(); i++)
    {
        word_stack.push_back(words_x[i]);
    }
    for (uint i=0; i<words_y.size(); i++)
    {
        word_stack.push_back(words_y[i]);
    }

    for (uint i=0; i<word_stack.size(); i++)        // sort word_stack by their size
    {
        for (uint j=i; j<word_stack.size(); j++)
        {
            if(word_stack[i]->size()>word_stack[j]->size())
            {
                tmp=word_stack[i];
                word_stack[i]=word_stack[j];
                word_stack[j]=tmp;
            }
        }
    }

    for (uint i=0; i<main_words.size(); i++)        // sort main_words by size
    {
        for (uint j=i; j<main_words.size(); j++)
        {
            if(main_words[i]->size()>main_words[j]->size())
            {
                tm=main_words[i];
                main_words[i]=main_words[j];
                main_words[j]=tm;
            }
        }
    }

    #ifdef DEBUG
    for (uint i=0; i<word_stack.size(); i++)
    {
        cout << "Word indicator sorted: " << i << ". " << word_stack[i]->get_name() << endl;
    }
    for (uint i=0; i<main_words.size(); i++)
    {
        cout << "Main words sorted: " << i << ". " << *main_words[i] << endl;
    }
    #endif // DEBUG
}

template <typename Data>
Crossword<Data>::Crossword(Data& board)
{
    if(shaping_words_x(board)||shaping_words_y(board))
    {
        clog << "no word was found in the crossword puzzle" << endl;
    }
    else
    {
        shaping_nodes(board);
        connecting();
    }

    for (uint i=0; i<board.words_size(); i++)
    {
        main_words.push_back(board.get_word(i));
    }

    counting_words(board);
    sort_words();

    max_x=board.size_x();
    max_y=board.size_y();

    #ifdef DEBUG
    cout << "Created Crossword" << endl;
    #endif
}

template <typename Data>
Crossword<Data>::~Crossword()
{
    for(uint i=0; i<knot.size(); i++)
    {
        #ifdef DEBUG
        cout << "Delete knot " << i << endl;
        #endif // DEBUG
        delete knot[i];
    }
    for(uint i=0; i<words_x.size(); i++)
    {
        #ifdef DEBUG
        cout << "Delete words_x " << i << endl;
        #endif // DEBUG
        delete words_x[i];
    }
    for(uint i=0; i<words_y.size(); i++)
    {
        #ifdef DEBUG
        cout << "Delete words_y " << i << endl;
        #endif // DEBUG
        delete words_y[i];
    }
    #ifdef DEBUG
    cout << "Deleted Crossword" << endl;
    #endif
}

/*template <typename Data>
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

    for (uint i=0; i<primary.main_words.size(); i++)
    {
        main_words.push_back();
    }

    for (uint i=0; i<primary.word_count.size(); i++)
    {
        word_count[i]=primary.word_count[i];
    }

    #ifdef DEBUG
    cout << "Copied crossword" << endl;
    #endif // DEBUG
}*/

template <typename Data>
void Crossword<Data>::write_in_console()        // for checking data in this class
{
    cout << endl << "Nodes:" << endl;
    for (uint i=0; i<knot.size(); i++)
    {
        cout << i << ". " << knot[i]->get_pos_x() << " " << knot[i]->get_pos_y() << " " << knot[i]->get_kar() << endl;
    }
    cout << endl << "Words_x" << endl;;
    for (uint i=0; i<words_x.size(); i++)
    {
        cout << i << ". " << words_x[i]->get_pos_x() << " " << words_x[i]->get_pos_y() << " " << words_x[i]->get_name() << endl;
    }
    cout << endl << "Words_y" << endl;
    for (uint i=0; i<words_y.size(); i++)
    {
        cout << i << ". " << words_y[i]->get_pos_x() << " " << words_y[i]->get_pos_y() << " " << words_y[i]->get_name() << endl;
    }
    cout << endl << "Word_stack" << endl;
    for (uint i=0; i<word_stack.size(); i++)
    {
        cout << i << ". " << word_stack[i]->get_pos_x() << " " << word_stack[i]->get_pos_y() << " " << word_stack[i]->get_name() << endl;
    }
    cout << endl << "Main_words" << endl;
    for (uint i=0; i<main_words.size(); i++)
    {
        cout << i << ". " << *main_words[i] << " size: " << main_words[i]->size() << endl;
    }
    cout << endl << "Word_count" << endl;
    for (uint i=0; i<word_count.size(); i++)
    {
        cout << i << ". " << word_count[i] << endl;
    }
    cout << endl << "Nodes words" << endl;
    for (uint i=0; i<knot.size(); i++)
    {
        cout << i << ". " << knot[i]->size() << " " << ((*knot[i])[0])->get_name() << " " << ((*knot[i])[1])->get_name() << endl;
    }
}

// checking functions

template <typename Data>
bool Crossword<Data>::check_words()         // check the amount of words and stack_word
{
    uint T[word_count.size()];
    for (uint i=0; i<word_count.size(); i++)
    {
        T[i]=0;
    }
    for(uint i=0; i<words_x.size(); i++)
    {
        if(words_x[i]->size()>word_count.size()) return true;
        T[words_x[i]->size()]++;
    }
    for(uint i=0; i<words_y.size(); i++)
    {
        if(words_y[i]->size()>word_count.size()) return true;
        T[words_y[i]->size()]++;
    }
    for (uint i=0; i<word_count.size(); i++)
    {
        if(T[i]!=word_count[i])
        {
            #ifdef DEBUG
            cout << "check_words: word_count:" << i << endl;
            #endif // DEBUG
            return true;
        }
    }

    return false;
}

template <typename Data>
bool Crossword<Data>::recursion_word(bool if_free[], std::vector<Word*>& relative, std::vector<uint>& if_free_relative, Word* beginning, uint which_node)
{
    Word* tmp_word;//, check_word;     // if(which_node+1>=beginning->size_node())
    Node* tmp_node;
    bool if_break=false;
    uint where_rel=relative.size()-1, counter=0;

    #ifdef DEBUG
    cout << "recursion: beginning !!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    #endif

    for (uint k=0; k<beginning->size_node()&&!if_break; k++)        // checking all nodes in this stack_word if busy or not
    {                                                               // only usable nodes in word_stack
        tmp_node=(*beginning)%k;
        #ifdef DEBUG
        cout << "recursion: k: " << k << " node: " << tmp_node->get_kar() << endl;
        #endif
        for (uint p=0; p<tmp_node->size(); p++)     // only 2 times
        {
            tmp_word=(*tmp_node)[p];

            if(tmp_word==beginning)     // if the same words
            {
                continue;
            }

            if(tmp_word->busy())
            {
                continue;
            }
            else
            {
                which_node=k;
                if_break=true;
                break;
            }
            return true;            // all the nodes/stack_word are full

        }
        counter++;
    }
    if(counter==beginning->size_node()&&!if_break)      // if no more free node
    {
        #ifdef DEBUG
        cout << "recursion: counter==beginning->size_node()" << endl;
        #endif // DEBUG
        return true;
    }

    #ifdef DEBUG
    cout << "recursion node: x: " << tmp_node->get_pos_x() << " y: " << tmp_node->get_pos_y() << " " << tmp_node->get_kar() << endl;
    #endif // DEBUG

    for (uint i=0; i<main_words.size(); i++)
    {
        if(if_free[i])
        {
            if(tmp_word->check_nodes(main_words[i]))        // nodes in word, if worked
            {
                tmp_word->change_name(*main_words[i]);

                if_free[i]=false;
                relative.push_back(tmp_word);
                if_free_relative.push_back(i);
                where_rel=relative.size()-1;

                #ifdef DEBUG
                cout << endl << "recursion: Changed name" << endl << endl;
                #endif // DEBUG

                if(recursion_word(if_free, relative, if_free_relative, tmp_word, 0))    // recursion to the another word
                {
                    if(beginning->size_node()>which_node+1)
                    {
                        #ifdef DEBUG
                        cout << endl << "recursion: second recursion" << endl << endl;
                        #endif // DEBUG
                        if(recursion_word(if_free, relative, if_free_relative, beginning, which_node+1))        // recursion to the maybe next word
                        {
                            return true;
                        }
                        else                                                                 // if the upper recursion end and this recursion fail
                        {                                                                       // delete the upper
                            for (uint p=relative.size()-1; p>=where_rel; p--)
                            {
                                #ifdef DEBUG
                                cout << "           erase word " << relative[p]->get_name() << endl;
                                #endif // DEBUG
                                relative[p]->erase();                           // delete from the latest
                                if_free[if_free_relative[p]]=true;
                                relative.pop_back();
                                if_free_relative.pop_back();
                            }
                            continue;                                           // checking another word in node
                        }
                    }
                    else                                                        // no more node available
                    {
                        return true;
                    }

                }
                else                                                         // if the upper recursion end and this recursion fail
                {
                    for (uint p=relative.size()-1; p>=where_rel; p--)
                    {
                        #ifdef DEBUG
                        cout << "           erase word " << relative[p]->get_name() << endl;
                        #endif // DEBUG
                        relative[p]->erase();                           // delete from the latest
                        if_free[if_free_relative[p]]=true;
                        relative.pop_back();
                        if_free_relative.pop_back();
                    }
                }
            }
        }
    }
    #ifdef DEBUG
    cout << "           if any of word does not fit" << endl;
    #endif // DEBUG
    return false;

}

template <typename Data>            // VOID '_'
bool Crossword<Data>::check_solution()  // main_words.size()==word_stack.size()
{
    if(this->check_words()) // if data good
    {
        #ifdef DEBUG
        cout << "check_solution: words doesnt fit" << endl;
        #endif // DEBUG
        return false;
    }

    bool if_free[main_words.size()];  // checking used specific words
    bool if_end=false;
    std::vector<Word*> relative;
    std::vector<uint> if_free_relative;

    for (uint i=0; i<main_words.size(); i++)
    {
        if_free[i]=true;
    }

    for (uint i=1; i<word_count.size()&&!if_end; i++)
    {
        for(uint j=word_count[i-1]; j<word_count[i]; j++)       // take only the smallest words, they are sorted
        {
            if_end=true;            // at least once loop only needed
            word_stack[0]->change_name(*main_words[j]);         // must be 0, no errors
            if_free[j]=false;
            relative.push_back(word_stack[j]);
            if_free_relative.push_back(j);

            #ifdef DEBUG
            cout << "check_solution: beginning" << endl;
            #endif // DEBUG

            if(recursion_word(if_free, relative, if_free_relative, word_stack[0], 0))
            {
                #ifdef DEBUG
                cout << "Found solution to Crossword" << endl;
                #endif // DEBUG
                return true;
            }
            else
            {
                #ifdef DEBUG
                cout << "check_solution: again " << j << endl;
                #endif // DEBUG
                word_stack[0]->erase();
                if_free[j]=true;
                if(relative.size()!=1)
                {
                    #ifdef DEBUG
                    clog << "               check_solution: relative vector have too many arguments " << relative.size() << endl;
                    #endif // DEBUG
                }
                if(if_free_relative.size()!=1)
                {
                    #ifdef DEBUG
                    clog << "               check_solution: if_free_relative vector have too many arguments " << if_free_relative.size() << endl;
                    #endif // DEBUG
                }
                relative.clear();
                if_free_relative.clear();
            }

        }
    }

    return false;
}

template <typename Data>
Data* Crossword<Data>::release(const char& filling)
{
    if(check_solution())
    {
        char T[max_x][max_y];
        bool if_break=false;
        Data *tmp_data = new Data;
        string tmp;

        for (uint i=0; i<max_y; i++)
        {
            for (uint j=0; j<max_x; j++)
            {
                T[j][i]=filling;
            }
        }

        for (uint l=0; l<words_x.size(); l++)
        {
            for (uint i=0; i<max_y&&!if_break; i++)
            {
                for (uint j=0; j<max_x&&!if_break; j++)
                {
                    if(words_x[l]->get_pos_x()==j&&words_x[l]->get_pos_y()==i)
                    {
                        if_break=true;
                        for (uint p=0; p<words_x[l]->size(); p++)
                        {
                            T[j+p][i]=(*words_x[l])[p];
                        }

                    }
                }
            }
            if_break=false;
        }

        for (uint l=0; l<words_y.size(); l++)
        {
            for (uint i=0; i<max_x&&!if_break; i++)
            {
                for (uint j=0; j<max_y&&!if_break; j++)
                {
                    if(words_y[l]->get_pos_x()==i&&words_y[l]->get_pos_y()==j)
                    {
                        if_break=true;
                        for (uint p=0; p<words_y[l]->size(); p++)
                        {
                            T[i][j+p]=(*words_y[l])[p];
                        }

                    }
                }
            }
            if_break=false;
        }

        for (uint i=0; i<max_y; i++)
        {
            for (uint j=0; j<max_x; j++)
            {
                tmp=tmp+T[j][i];
            }
            #ifdef DEBUG
            cout << tmp << endl;
            #endif // DEBUG
            tmp_data->push_back(tmp);
            tmp.clear();
        }

        return tmp_data;
    }
    else
    {
        return nullptr;
    }
}


#endif // CROSSWORD_H
