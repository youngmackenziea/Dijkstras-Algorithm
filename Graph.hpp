#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <climits>
#include <queue>

#include "GraphBase.hpp"

typedef std::string VERTEX_LABEL; //Name of the vertex
typedef unsigned long EDGE_WEIGHT; //Weight of the undirected edge
typedef std::map<VERTEX_LABEL, EDGE_WEIGHT> ADJACENCY; //Inside Matrix
typedef std::map<VERTEX_LABEL, ADJACENCY> GRAPH_MATRIX; //Outside Matrix
typedef std::pair<EDGE_WEIGHT, VERTEX_LABEL> PQ_ELEM; //Priority Queue Elements, the first element in the pair is the "priority"

class Graph : public GraphBase
{
public:
    void addVertex(std::string label);
    void removeVertex(std::string label);
    void addEdge(std::string label1, std::string label2, unsigned long weight);
    void removeEdge(std::string label1, std::string label2);
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);

    bool labelExists(VERTEX_LABEL label); // Check if a vertex with the argument label already exists in the graph
    unsigned long getEdgeWeight(VERTEX_LABEL label1, VERTEX_LABEL label2); //Returns the weight of the edge between two vertices, given that both vertices exist in the graph and both vertices are different

private:
    GRAPH_MATRIX verticesMap; //Perhaps call this GRAPH graph
};

#endif /* GRAPH_H */
