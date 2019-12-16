#ifndef Graph_H
#define Graph_H

#include <vector>
#include <list>
#include <cassert>
 
/*
klasa grafow zapewniajaca reprezentacje w postaci tablicy list sasiedztwa
*/
class Graph
{
    public:
    using vertex_t = size_t;
    using weight_t = unsigned int;    

    // krawedz grafu
    class Edge 
    {
        public:
        vertex_t first, second;
        weight_t weight;

        bool compare(Edge right)
        {
            return this->weight < right.weight;
        }
    };

    // pochodna struktura od Edge przeznaczona do tablic sasiedztwa 
    struct GraphNode
    {
        vertex_t vertex;
        weight_t weight;
    };

    std::vector<std::list<GraphNode>> data; // wektor list sąsiedztwa
    weight_t weight;
    
    Graph(size_t size) : weight(0)
    {
        data.resize(size);
    };
    
    Graph() : weight(0)
    {
    };

    size_t vertexCount()
    {
        return data.size();
    }

    void addEdge(const Edge &edge)
    {
        GraphNode node;

        if( (edge.first>edge.second?edge.first:edge.second) >= data.size())
            data.resize((edge.first>edge.second?edge.first:edge.second) +1);

        weight += edge.weight;
        node.vertex = edge.second;
        node.weight = edge.weight;
        data[edge.first].push_front(node);

        node.vertex = edge.first;
        node.weight = edge.weight;
        data[edge.second].push_front(node);
    };

    template<typename StreamType>
    void print(StreamType &stream) const
    {
        stream<<"Tree weight = "<<weight<<std::endl;
        if(data.empty())
        {
            stream<<"Graph is empty!"<<std::endl;
            return;
        }

        for( size_t v=0; v<data.size(); v++)
        {
            stream<<"Vertex "<<v<<" - ";
            for( auto node: data[v])
                stream<<node.vertex<<":"<<node.weight<<" ";
            stream<<std::endl;
        }
    };
};




#endif
