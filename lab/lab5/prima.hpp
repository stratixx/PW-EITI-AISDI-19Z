#ifndef Prima_H
#define Prima_H

#include "heap.hpp"
#include "graph.hpp"
#include <vector>
#include <cassert>

/*
Wymaga:
struktura krawędzi
    dwa wierzchołki i waga krawędzi
struktura przekształcająca krawędź w element listy
    zawiera numer wierzchołka, wagę i wskazanie na element listy
kolejka priorytetowa n-elementowa na typ krawędzi - kopiec
    front, pop, push
tablica list sąsiedztwa n-elementowa
    indeks tablicy odpowiada numerowi wierzchołka
    do list pushFront wkłądane są elementy budowane na podstawie krawędzi
    addEdge, getList, print
Wykonuje:
    inicjacja struktur
    tablica bool visited
*/
class Prima
{
    public:

    static void process( Graph &minSpanTree, Graph &graph )
    {
        std::vector<bool> visited(graph.vertexCount(), false);
        size_t vertex = 0;
        Graph::Edge edge;
        Heap<Graph::Edge> queue;

        // petla wykona sie vertexCount-1 razy
        for( size_t count = graph.vertexCount()-1; count; count--)
        {
            // biezacy wierzcholek odwiedzony
            visited[vertex] = true; 
            
            // lista sasiadow biezacego wierzcholka
            auto neighborList = graph.data[vertex]; 
            // iteracja po wszystkich sasiadach
            // jesli sasiad jeszcze nie odwiedzony, dodaj krawedz do kolejki priorytetowej
            for( auto neighborIter = neighborList.begin(); neighborIter!=neighborList.end(); ++neighborIter )
                if(!visited[neighborIter->vertex])
                    queue.push({vertex, neighborIter->vertex, neighborIter->weight});
        
            // wybierz nieodwiedzony wierzcholek o najmniejszym koszcie sciezki
            do
            {
                edge = queue.front();
                queue.pop();
            } while (visited[edge.second]);
            
            //dodanie wybranego wierzcholka do grafu wynikowego
            minSpanTree.addEdge(edge);
            vertex = edge.second;
        }
    }

    template<typename StreamType>
    static void test(StreamType &stream) 
    {
        Graph graph, minSpanTree, pattern;
        
        cout<<"-----------Prima Test Start-----------"<<endl;

        // stworzenie nieskierowanego spójnego grafu
        graph.addEdge({0, 1, 5}); graph.addEdge({0, 3, 9}); graph.addEdge({0, 6, 3});
        graph.addEdge({1, 2, 9}); graph.addEdge({1, 4, 8}); graph.addEdge({1, 5, 6}); graph.addEdge({1, 7, 7}); 
        graph.addEdge({2, 3, 9}); graph.addEdge({2, 4, 4}); graph.addEdge({2, 6, 5}); graph.addEdge({2, 7, 3}); 
        graph.addEdge({3, 6, 8});
        graph.addEdge({4, 5, 2}); graph.addEdge({4, 6, 1}); 
        graph.addEdge({5, 6, 6});
        graph.addEdge({6, 7, 9});

        // graf wynikowy
        pattern.addEdge({0, 1, 5}); pattern.addEdge({0, 6, 3});
        pattern.addEdge({2, 7, 3}); pattern.addEdge({2, 4, 4});  
        pattern.addEdge({4, 5, 2}); pattern.addEdge({4, 6, 1}); 
        pattern.addEdge({6, 3, 8});


        stream<<"Input graph"<<endl;
        graph.print(stream);

        stream<<"Processing graph with ";
        Prima::process(minSpanTree, graph); stream<<"Prima algorithm"<<endl;
        stream<<"Processed graph"<<endl;
        minSpanTree.print(stream);
        stream<<"Expected pattern graph"<<endl;
        pattern.print(stream);
        //assert(pattern==Graph);
        //stream<<"Test pattern==Graph OK"<<endl;
        stream<<"-----------Prima Test End-----------"<<endl;
        
    }

};




#endif
