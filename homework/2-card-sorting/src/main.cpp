/*
Autor: Konrad Winnicki
Utworzono: 03.11.2019

Implementacja algorytmu w 169 linii pliku

Zadanie:
    *   Wygeneruj losową permutację standardowej talii kart.
    *   Posortuj uzyskany ciąg kart w porządku rosnącym w sposób stabilny
    *   wykorzystując stabilny algorytm selection sort i strukturę listy.
*/

#include <iostream>
#include <list>
#include <algorithm>    // std::for_each
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////

class Card
{
    public:

    int number;
    int colour;

    static vector<std::string> numberString;
    static vector<std::string> colourString;

    const std::string& getNumberString()
    {
        return Card::numberString[number];
    }

    const std::string& getColourString()
    {
        return Card::colourString[colour];
    }

    bool operator==(const Card& card)
    {
        return (this->colour==card.colour)&&(this->number==card.number);
    }

    static bool lessColour(const Card& left, const Card& right)
    {
        return left.colour<right.colour;
    }

    static bool lessNumber(const Card& left, const Card& right)
    {
        return left.number<right.number;
    }
};

typedef list<Card> deck_t;
typedef bool (*card_cmp_fun_t)(const Card&, const Card&);

deck_t& generate(deck_t&);
deck_t& shuffle(deck_t&);
void printDeck(deck_t&);
deck_t& selectionSortStable(deck_t&, card_cmp_fun_t);



//vector<std::string> Card::colourString = { "Pik", "Kier", "Trefl", "Karo" };
vector<std::string> Card::colourString = { "\u2660", "\u2666", "\u2663", "\u2764" };
vector<std::string> Card::numberString = { "2", "3", "4", "5", "6", "7", 
                                            "8", "9", "10", "J", "Q", "K", "A" };
///////////////////////////////////////////////////////////////


int main(int argc, char * argv[])
{
    deck_t deck;

    generate(deck);
    cout<<"Deck size: "<<deck.size()<<endl;

    cout<<"Shuffle start..."<<endl;
    shuffle(deck); 
    shuffle(deck); 
    shuffle(deck);
    cout<<"Shuffle end."<<endl;

    //printDeck(deck);

    cout<<"Unsorted"<<endl;
    printDeck(deck);
    cout<<"-------------------------------"<<endl;

    cout<<"Sorting by colour"<<endl;
    selectionSortStable(deck, Card::lessColour);
    printDeck(deck);
    cout<<"-------------------------------"<<endl;

    cout<<"Sorting by number"<<endl;
    selectionSortStable(deck, Card::lessNumber);
    printDeck(deck);
    cout<<"-------------------------------"<<endl;

    cout<<"Again sorting by colour"<<endl;
    selectionSortStable(deck, Card::lessColour);
    printDeck(deck);
    cout<<"-------------------------------"<<endl;

    
    return 0;
}


deck_t& generate(deck_t& deck)
{
    Card card;

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
    Card card;
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

void printCard(Card card)
{
    //cout<<"Card( Number: "<<card.getNumberString()<<"\tColour: "<<card.getColourString()<<" )"<<endl;
    cout<<card.getNumberString()<<" "<<card.getColourString()<<endl;
}

void printDeck(deck_t& deck)
{
    cout<<"Printing deck..."<<endl;
    for_each(deck.begin(), deck.end(), printCard);
    cout<<"Deck printed."<<endl;
}

deck_t& selectionSortStable(deck_t& listSortable, card_cmp_fun_t compareLess)
{
    // obecna implementacja jest niestabilna
    deck_t::iterator i, j, k;
    Card card;

    for(i=listSortable.begin(); i!=listSortable.end(); )
    {
        k = i;
        //Szukanie najmniejszego elementu z nieposortowanych
        for(j=i; j!=listSortable.end(); ++j)
            if(compareLess(*j, *k))
                k = j;

        // wstawienie najmniejszego elementu jako kolejny z posortowanych
        if(i!=k)
        {
            card = *k;
            
            listSortable.remove(*k);
            listSortable.insert(i, card);
        }
        else
        {
            ++i;
        }
        
        ///swapCard(*k, *i);
    }

    return listSortable;
}
