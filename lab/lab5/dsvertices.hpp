#ifndef DS_Vertices_H
#define DS_Vertices_H

#include "graph.hpp"
#include <list>
#include <vector>
#include <cassert>


/*
Detachable set of vertices class
implementuje zbiory rozlaczne grafow
*/
class DSVertices
{
    public:
    using size_type = size_t;
    using Edge = Graph::Edge;

    struct DSNode
    {
        size_type up, rank;
    };

    std::vector<std::list<DSNode>> data;

    void makeSet(size_type vertice)
    {
        
    }

    size_type findSet(size_type vertice)
    {
        return vertice;
    }

    void unionSets(Edge edge)
    {

    }
};




#endif
