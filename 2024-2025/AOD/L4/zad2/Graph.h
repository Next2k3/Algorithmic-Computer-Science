#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <limits>

using namespace std;

class BipartiteGraph {
public:
    struct Edge {
        int to;
        int capacity;
        int flow;
    };

    BipartiteGraph(int k, int degree);
    int getMaxFlow();
    void printMatching() const;
    int getTotalVertices() const;
    int getEdgeCapacity(int from, int to) const;

private:
    int source, sink, totalVertices;
    vector<vector<Edge>> adjList;
    vector<int> pred;

    void addEdge(int from, int to, int capacity);
    bool bfs();
};

#endif // GRAPH_H
