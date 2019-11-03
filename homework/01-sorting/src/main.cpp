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
template<class Sortable> Sortable& selectionSort(Sortable&);
bool operator <(const card_t&, const card_t&);
///////////////////////////////////////////////////////////////


int main(int argc, char * argv[])
{
    deck_t deck;

    cout<<"hello World!"<<endl;

    generate(deck);
    cout<<"Deck size: "<<deck.size()<<endl;
    shuffle(deck);
    printDeck(deck);
    selectionSort(deck);
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
    cout<<"Shuffle "<<endl;
    return deck;
}

void printDeck(deck_t& deck)
{
    cout<<"Print deck "<<endl;
}

template<class Sortable>
Sortable& selectionSort(Sortable& sortable)
{
    cout<<"Selection Sort "<<endl;
    return sortable;
}

bool operator <(const card_t& left, const card_t& right)
{
    return (left.number<right.number);
}