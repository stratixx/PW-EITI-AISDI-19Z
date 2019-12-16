#ifndef Kruskal_H
#define Kruskal_H

#include "heap.hpp"
#include "graph.hpp"
#include "dsvertices.hpp"

class Kruskal
{
    public:

    static void process( Graph &minSpanTree, Heap<Graph::Edge> &graph )
    {
        
        // petla wykona sie vertexCount-1 razy
        for( size_t count = graph.size()-1; count; count--)
        {

        }
    }
    
    template<typename StreamType>
    static void test(StreamType &stream) 
    {
        Graph minSpanTree, pattern;
        Heap<Graph::Edge> graph;
        cout<<"-----------Kruskal Test Start-----------"<<endl;

        graph.push({0, 1, 5}); graph.push({0, 3, 9}); graph.push({0, 6, 3});
        graph.push({1, 2, 9}); graph.push({1, 4, 8}); graph.push({1, 5, 6}); graph.push({1, 7, 7}); 
        graph.push({2, 3, 9}); graph.push({2, 4, 4}); graph.push({2, 6, 5}); graph.push({2, 7, 3}); 
        graph.push({3, 6, 8});
        graph.push({4, 5, 2}); graph.push({4, 6, 1}); 
        graph.push({5, 6, 6});
        graph.push({6, 7, 9});

        
        pattern.addEdge({0, 1, 5}); pattern.addEdge({0, 6, 3});
        pattern.addEdge({2, 7, 3}); pattern.addEdge({2, 4, 4});  
        pattern.addEdge({4, 5, 2}); pattern.addEdge({4, 6, 1}); 
        pattern.addEdge({6, 3, 8});


        stream<<"Input graph"<<endl;
        graph.print(stream);

        stream<<"Processing graph with ";
        Kruskal::process(minSpanTree, graph); stream<<"Kruskal algorithm"<<endl;
        stream<<"Processed graph"<<endl;
        minSpanTree.print(stream);
        stream<<"Expected pattern graph"<<endl;
        pattern.print(stream);
        //assert(pattern==Graph);
        //stream<<"Test pattern==Graph OK"<<endl;
        stream<<"-----------Kruskal Test End-----------"<<endl;
        
    }
};




#endif
