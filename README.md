# Dijkstras-Algorithm
Dijksta's Algorithm is a greedy method algorithm used to find the shortest path between two nodes in a graph.

This implementation uses nested maps, each with key-value pairs. Each key of the "outside" map holds one node in the graph and each value holds the "inside" map of adjacent nodes. Each key of the "inside" map holds an adjacent node to the "outside" map's key (or node) and the value holds the weight between the two nodes. This weight is used to analyze the path length between nodes

A priority queue is used to implement the greedy algorithm. Each time a shorter total path is found, this path is inserted into the queue and the previous shortest path is popped from the top. The path remaining in the queue at the end is returned as the shortest path.
