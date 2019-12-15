#ifndef Kruskal_H
#define Kruskal_H

#include "heap.hpp"
#include "graph.hpp"

class Kruskal
{
    public:

    static void process( Graph &minSpanTree, Graph &graph )
    {

    }
    
    template<typename StreamType>
    static void test(StreamType &stream) 
    {
        Graph graph, minSpanTree, pattern;
        
        cout<<"-----------Kruskal Test Start-----------"<<endl;

        graph.addEdge({0, 1, 5}); graph.addEdge({0, 3, 9}); graph.addEdge({0, 6, 3});
        graph.addEdge({1, 2, 9}); graph.addEdge({1, 4, 8}); graph.addEdge({1, 5, 6}); graph.addEdge({1, 7, 7}); 
        graph.addEdge({2, 3, 9}); graph.addEdge({2, 4, 4}); graph.addEdge({2, 6, 5}); graph.addEdge({2, 7, 3}); 
        graph.addEdge({3, 6, 8});
        graph.addEdge({4, 5, 2}); graph.addEdge({4, 6, 1}); 
        graph.addEdge({5, 6, 6});
        graph.addEdge({6, 7, 9});

        
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
