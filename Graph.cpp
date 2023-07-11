#include "Graph.hpp"
//#include <iostream>

// Creates a vertex to the graph with a label & checks that no 2 vertices have the same label using ‘labelExists’ function
void Graph::addVertex(std::string label)
{
    if (!labelExists(label)) // if label does not exist
    {
        ADJACENCY adjacencyMap; // currently empty map
        verticesMap.insert({label, adjacencyMap});
    }
    else // if label already exists
    {
        throw("Label already exists.\n");
    }
}

// does vertex already exist in map?
// Looks at each key in the map and returns whether a vertex with the input label already exists 
bool Graph::labelExists(VERTEX_LABEL label)
{
    return (verticesMap.find(label) != verticesMap.end());
}

// Iterates through the adjacency map found at each “label” entry of the graph map & removes the edge between the starting vertex and destination vertex. 
// It then erases the entry from the outside, graph matrix 
void Graph::removeVertex(std::string label)
{
    if (labelExists(label)) // if label does exist
    {
        ADJACENCY::iterator it = verticesMap[label].begin(); // set iterator to the beginning of the adjacency map found at the "label" entry of the graph map
        while (it != (verticesMap[label].end()))               // As long as the iterator is not pointing to the end...
        {
            removeEdge(label, it->first); //...remove the edge between the "label" vertex (vertex1) and the it->first vertex (vertex2)
            it++;
        }                                 

        verticesMap.erase(label); // Remove the entry from the GRAPH MATRIX
    }
    else // if label does not exist
    {
        throw("This vertex already does not exist in the graph.");
    }
}

// Adds an edge between two inputted vertices & checks that both vertices’ labels exist and are not equivalent to each other
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
    if ((labelExists(label1) && labelExists(label2)) && (label1 != label2)) // if both vertices exist in the graph and are different 
    {
        // If need to improve time complexity, may need to edit for loop implementation (could add template to labelExists() and make a map parameter)
        for (ADJACENCY::iterator it = verticesMap[label1].begin(); it != verticesMap[label1].end(); ++it)
        {
            if (it->first == label2)
            {
                throw("This edge already exists in the graph.");
            }
        }

        verticesMap[label1].insert({label2, weight});
        verticesMap[label2].insert({label1, weight});
    }
}

// Removes an edge between two inputted vertex labels. As long as both labels exist, it is checked that the second vertex can be found within 
// the adjacency map of the first vertex.
void Graph::removeEdge(std::string label1, std::string label2)
{
    if (labelExists(label1) && labelExists(label2)) // If both vertices exist in the graph...
    {
        if (verticesMap[label1].find(label2) != verticesMap[label1].end())
        // ...and if vertex2 is found in the ADJACENCY MAP for vertex 1 (therefore vertex 1 is also found in the ADJACENCY MAP for vertex 2)...
        {
            verticesMap[label1].erase(label2); // remove vertex 2 from vertex 1's ADJACENCY MAP [O(logn)]
            verticesMap[label2].erase(label1); // remove vertex 1 from vertex 2's ADJACENCY MAP [O(logn)]
        }
    }
    else
    {
        throw "This edge does not exist in the graph.";
    }
}
// Returns weight for a path between two nodes  
unsigned long Graph::getEdgeWeight(VERTEX_LABEL label1, VERTEX_LABEL label2)
{
    //ADJACENCY::iterator it = verticesMap[label1].find(label2)
    //return it->second; 

    return verticesMap[label1][label2];
}

// Finds the shortest possible path between two inputted vertices using 2 maps, shortestDist and prev
// Also uses a priority queue called paths to store the distances  
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) 
{
    std::priority_queue<PQ_ELEM, std::vector<PQ_ELEM>, std::greater<PQ_ELEM>>  paths;
    std::map<VERTEX_LABEL, EDGE_WEIGHT> shortestDist; // map that holds pairs: first value is a key representing each vertex, second value holds the current shortest path distance for the key vertex
    std::map<VERTEX_LABEL, VERTEX_LABEL> prev; // map that holds pairs: first value is a key representing each vertex, second value is a key to a previous vertex
    
    for (auto v : verticesMap ) 
    {
        if (v.first == startLabel) // if vertex label is starting point
        {
            paths.push(PQ_ELEM(0, v.first)); // push (weight, label) pair onto priority queue... weight is 0 since it's starting point
            shortestDist.insert({v.first, 0}); // insert vertex with weight 0 into distance map
        }
        else
        {
            paths.push(PQ_ELEM(ULONG_MAX, v.first)); // otherwise, weight is set to infinity
            shortestDist.insert({v.first, ULONG_MAX}); // insert vertex with weight inifinity into distance map
            prev.insert({v.first, ""});
        }        
    }
    
    while (paths.empty() == false) // while priority queue is not empty
    {
        PQ_ELEM top = paths.top();
        paths.pop();

        for (auto v : verticesMap[top.second]) // for every adjacent vertex to top.second
        {
            
            unsigned long altDist = shortestDist[top.second] + getEdgeWeight(top.second, v.first); 
            if ((altDist < shortestDist[v.first]) && (shortestDist[top.second] != ULONG_MAX)) // if alternate distance is shorter than current shortest distance and top.second isn't infinity
            {
                shortestDist[v.first] = altDist; // replace shortest distance with alternate distance that's smaller
                prev[v.first] = top.second; // the vertex popped from the PQ is now the previous vertex
                paths.push(PQ_ELEM(altDist, v.first)); 
            }
        }
    }

    // Update path to show the shortest path from startLabel to endLabel
    VERTEX_LABEL i = endLabel;
    for (;;) // This loop recreated the path in reverse order (endLabel to startLabel)
    {
        path.push_back(i);
        if (i == startLabel)
        {
            break;
        }
        i = prev[i];
    } 

    for (auto first = path.begin(), last = path.end() - 1; first < last; first++, last--) // Reverse the contents of the path vector
    {
        swap(*first, *last); 
    }

    return shortestDist[endLabel]; // Returns the unsigned long value of the shortest path from start to end
}