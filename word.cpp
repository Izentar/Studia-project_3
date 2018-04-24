#ifndef WORD_CPP
#define WORD_CPP

#include "word.h"

#define VOID '_'

using namespace std;


Word::Word(const uint& x, const uint& y, const char& vert)
:pos_x(x), pos_y(y), pos(0), used(false)
{
    if(vert=='x'||vert=='X')
    {
        pos=1;
    }
    else
    if(vert=='y'||vert=='Y')
    {
        pos=2;
    }
}

Word::~Word() {}

bool Word::connect_node(Node* nod)
{
    for (uint i=0; i<word_nodes.size(); i++)
    {
        if(word_nodes[i]==nod)
        {
            #ifdef DEBUG
            cout << "There is already this node in this word" << word_stock << endl;
            #endif //DEBUG
            return true;
        }
    }
    word_nodes.push_back(nod);
    return false;
}

void Word::resize(uint& number)
{
    stringstream ss;
    for (uint i=0; i<number; i++)
    {
        ss<<VOID;
    }
    word_stock=ss.str();
    word_nodes.clear();
    used=false;
}

bool Word::change_name(const string& name)
{
    used=true;
    if(name.size()!=word_stock.size())
    {
        #ifdef DEBUG
        cout << "Word: changed word_stock: wrong size" << endl;
        #endif // DEBUG
        return true;
    }
    word_stock=name;

    if(pos==1)
    {
        for (uint i=0; i<word_nodes.size(); i++)
        {
            for (uint j=0; j<name.size(); j++)
            {
                if(word_nodes[i]->get_pos_x()==pos_x+j)
                {
                    word_nodes[i]->change_kar(name[j]);
                    break;
                }
            }
        }
    }
    else
    if(pos==2)
    {
        for (uint i=0; i<word_nodes.size(); i++)
        {
            for (uint j=0; j<name.size(); j++)
            {
                if(word_nodes[i]->get_pos_y()==pos_y+j)
                {
                    word_nodes[i]->change_kar(name[j]);
                    break;
                }
            }
        }
    }
    else
    {
        #ifdef DEBUG
        cout << "Word: wrong changed word_stock: wrong pos" << endl;
        #endif // DEBUG
        return true;
    }

    #ifdef DEBUG
    cout << "Word: changed word_stock " << name << endl;
    #endif // DEBUG
    return false;
}

string Word::get_name() const
{
    return word_stock;
}

char Word::operator[] (const uint& index) const
{
    if(index>=word_stock.size())
    {
        #ifdef DEBUG
        clog << "Word []: going out of range" << endl;
        #endif // DEBUG
        return VOID;
    }

    return word_stock[index];
}

Node* Word::operator% (const uint& index) const
{
    if(index>=word_nodes.size())
    {
        #ifdef DEBUG
        cout << "Word %: going out of range" << endl;
        clog << "Word %: going out of range" << endl;
        #endif // DEBUG
        return nullptr;
    }

    return word_nodes[index];
}

uint Word::get_pos_x() const
{
    return pos_x;
}

uint Word::get_pos_y() const
{
    return pos_y;
}

uint Word::size() const
{
    return word_stock.size();
}

uint Word::size_node() const
{
    return word_nodes.size();
}

bool Word::busy() const
{
    return used;
}

void Word::erase()
{
    if(used==false)
    {
        return;
    }

    used=false;
    stringstream ss;
    for (uint i=0; i<word_stock.size(); i++)
    {
        ss<<VOID;
    }

    word_stock=ss.str();

    for (uint i=0; i<word_nodes.size(); i++)
    {
        //for (uint j=0; j<word_nodes[i]->size(); j++)        // only 2 times
        //{
            if(!(*word_nodes[i])[0]->busy()&&!(*word_nodes[i])[1]->busy())
            {
                word_nodes[i]->change_kar(VOID);
            }
        //}
    }
}


bool Word::check_nodes(const string* name)
{
    if(this->size()!=name->size())
    {
        return false;
    }

    #ifdef DEBUG
    clog << endl <<  "          check_nodes: pos: " << pos <<  endl;
    #endif // DEBUG
    if(pos==1)
    {
        for (uint i=0; i<word_nodes.size(); i++)
        {
            if(!(word_nodes[i]->get_kar()==VOID||word_nodes[i]->get_kar()==((*name)[word_nodes[i]->get_pos_x()-pos_x])))
            {
                #ifdef DEBUG
                clog <<  "          check_nodes: name: " << *name <<  " name[]:" << ((*name)[word_nodes[i]->get_pos_x()-pos_x]) << " get_kar: " << word_nodes[i]->get_kar() << " posx " << word_nodes[i]->get_pos_x() << " posy " << word_nodes[i]->get_pos_y() <<  endl;
                #endif // DEBUG
                return false;
            }
        }

        return true;
    }
    else
    if(pos==2)
    {
        for (uint i=0; i<word_nodes.size(); i++)
        {
            if(!(word_nodes[i]->get_kar()==VOID||word_nodes[i]->get_kar()==((*name)[word_nodes[i]->get_pos_y()-pos_y])))
            {
                #ifdef DEBUG
                clog <<  "check_nodes: name: " << *name << " name[]:" << ((*name)[word_nodes[i]->get_pos_y()-pos_y]) << " get_kar: " << word_nodes[i]->get_kar() << " posx " << word_nodes[i]->get_pos_x() << " posy " << word_nodes[i]->get_pos_y() <<  endl;
                #endif // DEBUG
                return false;
            }

        }
        return true;
    }
    else
    {
        return false;
    }

    return true;
}

/*uint Word::size_bool() const
{
    return already_checked.size();
}

bool Word::bool_check(const uint& index) const
{
    if(index>=word_stock.size())
    {
        #ifdef DEBUG
        clog << "Word bool_check: out of range" << endl;
        #endif // DEBUG
        return false;
    }

    return already_checked[index];
}

void Word::bool_push_back(const bool& war)
{

}*/


#endif // WORD_CPP
