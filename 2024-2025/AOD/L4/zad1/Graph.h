#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <queue>
#include <random>

using namespace std;

class Graph {
public:
    Graph(int k);
    pair<int, int> edmondsKarp();
    void printFlowDetails() const;
    int getTotalVertices() const;
    int getEdgeCapacity(int from, int to) const;

private:
    int k;
    int totalVertices;
    vector<vector<int>> edgesCapacities;

    void initializeEdges();
    int hammingWeight(int x) const;
};


#endif // GRAPH_H
