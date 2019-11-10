/*
Autor: Konrad Winnicki
Utworzono: 03.11.2019

Zadanie:
    *   Wygeneruj losową permutację standardowej talii kart.
    *   Posortuj uzyskany ciąg kart w porządku rosnącym w sposób stabilny
    *   wykorzystując algorytm selection sort i strukturę listy.
*/

#include <iostream>
#include <list>
#include <algorithm>    // std::for_each

using namespace std;

////////////////////////////////////////////////////////////

struct card_t
{
    int number;
    int colour;
};

typedef list<card_t> deck_t;

deck_t& generate(deck_t&);
deck_t& shuffle(deck_t&);
void printDeck(deck_t&);
deck_t& selectionSortStable(deck_t&);
bool operator <(const card_t&, const card_t&);
void swapCard(card_t&, card_t&);

///////////////////////////////////////////////////////////////


int main(int argc, char * argv[])
{
    deck_t deck;

    generate(deck);
    cout<<"Deck size: "<<deck.size()<<endl;

    cout<<"Shuffle start..."<<endl;
    shuffle(deck); shuffle(deck); shuffle(deck);
    cout<<"Shuffle end."<<endl;

    printDeck(deck);
    selectionSortStable(deck);
    printDeck(deck);


    
    return 0;
}


deck_t& generate(deck_t& deck)
{
    card_t card;

    cout<<"Generate "<<endl;


    for(int number=0; number<(52/4); ++number)
        for( int colour=0; colour<4; ++colour)
        {
            card.colour = colour;
            card.number = number;

            deck.push_back(card);
        }

    return deck;
}

deck_t& shuffle(deck_t& deck)
{
    card_t card;
    deck_t::iterator iter;
    deck_t shuffledDeck;


    srand(time(NULL));

    iter = deck.begin();
    
    for(iter=deck.begin(); iter!=deck.end(); ++iter)
    {
        if(rand()%2)
            shuffledDeck.push_front(*iter);
        else
            shuffledDeck.push_back(*iter);
    }
    deck = shuffledDeck;

    return deck;
}

void printCard(card_t card)
{
    cout<<"Card( Number: "<<card.number<<"\tColour: "<<card.colour<<" )"<<endl;
}

void printDeck(deck_t& deck)
{
    cout<<"Printing deck..."<<endl;
    for_each(deck.begin(), deck.end(), printCard);
    cout<<"Deck printed."<<endl;
}

deck_t& selectionSortStable(deck_t& listSortable)
{
    // obecna implementacja jest niestabilna
    deck_t::iterator i, j, k;

    for(i=listSortable.begin(); i!=listSortable.end(); ++i)
    {
        k = i;
        for(j=i; j!=listSortable.end(); ++j)
            if(*j < *k)
                k = j;
        swapCard(*k, *i);
    }

    return listSortable;
}

bool operator <(const card_t& left, const card_t& right)
{
    return (left.number<right.number);
}

void swapCard(card_t& left, card_t& right)
{
    card_t tmp;
    tmp = left;
    left = right;
    right = tmp;
}