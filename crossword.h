#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <iostream>
#include <string>
#include <vector>

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

    bool shaping_words_x(Data&);
    bool shaping_words_y(Data&);
    void shaping_nodes(Data&);
    void connecting();
    void counting_words(Data&);
    bool recursion(bool if_free[], Word* beginning);
    bool recursion_nodes(bool if_free[], std::vector<Word*>& , Word* , uint);

public:

    Crossword(Data&);
    ~Crossword();
    Crossword(Crossword&);

    void write_in_console();
    bool check_words();
    void sort_words();
    bool check_solution();
    bool check_crossword();
    Data release();

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
    cout << count << endl;

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
                cout << "connected node to word and word to node: " << words_x[a]->get_name() << endl;
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
                cout << "connected node to word and word to node: " << words_y[a]->get_name() << endl;
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
void Crossword<Data>::write_in_console()
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
        cout << i << ". " << *main_words[i] << endl;
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
bool Crossword<Data>::check_words()
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

/*template <typename Data>
bool Crossword<Data>::recursion(bool if_free[], Word* beginning)        // return true, OK
{
    Word* tmp_word;
    Node* tmp_node;
    bool if_break=false;//, if_good=true;
    uint counter=0;

    for (uint i=0; i<beginning->size_node(); i++)       // nodes
    {
        go_back[i][0]=false;
        if_break=false;
        tmp_node=(*beginning)%i;
        for (uint j=0; j<tmp_node->size(); j++)      // DO NOT WORRY, words in node, for now only 2 times
        {
            tmp_word=(*tmp_node)[j];

            if(tmp_word==beginning)     // if the same words
            {
                continue;
            }

            if(tmp_word->busy())                                                // not free, end
            {
                #ifdef DEBUG
                cout << "recursion: the word_stock[] is already used" << endl;
                #endif
                counter++;
                continue;
            }
        }
    }
}*/

/*template <typename Data>
void Crossword<Data>::words_erase(bool relative[], Word* beginning, uint& which_node)
{

}*/


template <typename Data>                                                                        // for 1 node method
bool Crossword<Data>::recursion_nodes(bool if_free[], std::vector<Word*>& relative, Word* beginning, uint which_node)        // return true, upper was OK
{
    Word* tmp_word;     // if(which_node+1>=beginning->size_node())
    Node* tmp_node;
    bool if_break=false;
    uint where_rel, counter=0;

    tmp_node=(*beginning)%which_node;
    for (uint j=0; j<tmp_node->size(); j++)      // DO NOT WORRY, words in node, for now only 2 times
    {
        #ifdef DEBUG
        cout << "recursion_nodes: beginning " << tmp_node->size() << endl;
        #endif
        tmp_word=(*tmp_node)[j];

        if(tmp_word==beginning)     // if the same words
        {
            continue;
        }

        if(tmp_word->busy())                                                // not free, end
        {
            #ifdef DEBUG
            cout << "recursion: the word_stock[] is already used" << endl;
            #endif
            return true;
        }
        else
        {
            #ifdef DEBUG
            cout << endl << "recursion_nodes: start checking " << tmp_node->size() << endl << endl;
            #endif

            for (uint k=0; k<main_words.size()&&!if_break; k++)             // checking all main words
            {
                if(if_free[k])                                              // if not used
                {
                    #ifdef DEBUG
                    cout << endl << "recursion_nodes: founded if_free " << k << endl << endl;
                    #endif
                    if(tmp_word->check_nodes(main_words[k]))        // nodes in word, if worked
                    {
                        tmp_word->change_name(*main_words[k]);
                        if_free[k]=false;
                        relative.push_back(tmp_word);
                        where_rel=relative.size()-1;

                        #ifdef DEBUG
                        cout << endl << "recursion: Changed name" << endl << endl;
                        #endif // DEBUG

                        for (uint l=0; l<tmp_word->size_node(); l++)        // check next nodes in new word
                        {

                            if(recursion_nodes(if_free, relative, tmp_word, l))       // all words upper were right
                            {
                                counter++;
                                continue;
                            }
                            else                                // maybe another word in this recursion will fit here
                            {
                                for (uint p=relative.size()-1; p>where_rel; p--)
                                {
                                    relative[p]->erase();                           // delete from the latest
                                    relative.pop_back();
                                }
                                tmp_word->erase();
                                if_free[k]=true;
                                break;
                            }
                        }
                        if(counter==tmp_word->size_node())
                        {
                            counter=0;
                            if_break=true;
                        }
                        else
                        {
                            counter=0;
                            if_break=false;
                        }
                    }
                }
            }

            if(if_break)    // all words upper were right
            {
                #ifdef DEBUG
                cout << "recursion_node: if_break=true" << endl;
                #endif // DEBUG
                return true;
            }
            else            // no word there fit here
            {
                #ifdef DEBUG
                cout << "recursion_node: if_break=false" << endl;
                #endif // DEBUG
                return false;
            }
        }

    }

    #ifdef DEBUG
    cout << endl << "recursion_node: should never be there" << endl << endl;
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
        return true;
    }

    bool if_free[main_words.size()];  // checking used specific words
    bool if_end=false, if_find=false;
    std::vector<Word*> relative;

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

            #ifdef DEBUG
            cout << "check_solution: beginning" << endl;
            #endif // DEBUG

            if(recursion_nodes(if_free, relative, word_stack[j], 0))
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
                word_stack[j]->erase();
                if_free[j]=true;
                if(relative.size()>1)
                {
                    #ifdef DEBUG
                    clog << "check_solution: relative vector have too many arguments " << j << endl;
                    #endif // DEBUG
                }
                relative.clear();
            }

        }
    }

    return false;
}


template <typename Data>
bool Crossword<Data>::check_crossword()
{

}

template <typename Data>
Data Crossword<Data>::release()
{

}


#endif // CROSSWORD_H
