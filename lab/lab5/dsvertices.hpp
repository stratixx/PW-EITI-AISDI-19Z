#ifndef DS_Vertices_H
#define DS_Vertices_H

#include <vector>


/*
Detachable set of vertices class
implementuje zbiory rozlaczne grafow
zastosowana struktura drzewa skierowanego
*/
class DSVertices
{
    public:
    using size_type = size_t;

    struct DSNode
    {
        size_type parent; // 
        size_type rank;
    };

    std::vector<DSNode> data;

    DSVertices() = default;

    DSVertices(size_type verticeCount)
    {
        data.resize(verticeCount);
        for( size_type n=0; n<data.size(); ++n)
        {
            data[n].parent = n;
            data[n].rank = 0;            
        }
    };

    void makeSet(size_type vertice)
    {
        if( vertice>=data.size())
            data.resize(vertice+1);

        data[vertice].parent = vertice;
        data[vertice].rank = 0;
    }

    /*
        Wyszukiwanie reprezentanta zbioru
        zwraca korzeń drzewa danego zbioru
        przy każdym wyszukaniu minimalizuje wysokość drzewa
    */
    size_type findSet(size_type vertice)
    {
        if( data[vertice].parent == vertice )
            return vertice;

        data[vertice].parent = findSet(data[vertice].parent);
        return data[vertice].parent;
    }

    /*
        łączenie zbiorów rozłacznych
        dołącza mniejsze drzewo do większego
    */
    void unionSets(size_type first, size_type second)
    {
        size_type firstRoot = findSet(first);
        size_type secondRoot = findSet(second);

        if( data[firstRoot].rank > data[secondRoot].rank )
            data[secondRoot].parent = firstRoot;
        else if( data[firstRoot].rank < data[secondRoot].rank )
            data[firstRoot].parent = secondRoot;
        else if( firstRoot!=secondRoot )
        {
            data[secondRoot].parent = firstRoot;
            ++data[firstRoot].rank;
        }
    }
};




#endif
