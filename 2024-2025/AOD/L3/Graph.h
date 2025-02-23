#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <limits>
#include <utility>
#include <string>
#include <stdexcept>

using namespace std;

struct Graph {
    int totalVertices;
    int totalEdges;
    vector<vector<pair<int, int>>> adjacencyList;
    int minEdgeWeight;
    int maxEdgeWeight;

    Graph(int vertices, int edges, int minWeight, int maxWeight);
};

Graph readGraphFromFile(const string& filename);
vector<int> readSourceVertices(const string& filename);
vector<pair<int, int>> readVertexPairs(const string& filename);
void writeSourceResults(const string& outputFilename, const string& graphFilename, const string& sourceFilename, const string& algorithmType, const Graph& graph, int minWeight, int maxWeight, double avgTime);
void writeVertexPairResults(const string& outputFilename, const string& graphFilename, const string& pairsFilename, const string& algorithmType, const Graph& graph, int minWeight, int maxWeight, const vector<tuple<int, int, int>>& vertexPairsWithResults);

#endif // GRAPH_H
