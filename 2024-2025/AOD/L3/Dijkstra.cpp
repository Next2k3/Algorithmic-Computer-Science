#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <tuple>
#include <stdexcept>
#include <chrono>
#include "Graph.h"

using namespace std;

pair<vector<int>, vector<int>> dijkstraAllShortestPaths(const Graph& graph, int source) {
    vector<int> distances(graph.totalVertices + 1, INT32_MAX);
    vector<int> predecessors(graph.totalVertices + 1, -1);

    distances[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, source);

    while (!pq.empty()) {
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (dist > distances[node]) continue;

        for (const auto& neighborEdge : graph.adjacencyList[node]) {
            int neighbor = neighborEdge.first;
            int cost = neighborEdge.second;

            int value = distances[node] + cost;
            if (distances[neighbor] > value) {
                distances[neighbor] = value;
                predecessors[neighbor] = node;
                pq.emplace(value, neighbor);
            }
        }
    }

    return {distances, predecessors};
}

int dijkstraShortestPathLength(const Graph& graph, int source, int target) {
    vector<int> distances(graph.totalVertices + 1, INT32_MAX);
    distances[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, source);

    while (!pq.empty()) {
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (node == target) return distances[node];

        if (dist > distances[node]) continue;

        for (const auto& neighborEdge : graph.adjacencyList[node]) {
            int neighbor = neighborEdge.first;
            int cost = neighborEdge.second;

            int value = distances[node] + cost;
            if (distances[neighbor] > value) {
                distances[neighbor] = value;
                pq.emplace(value, neighbor);
            }
        }
    }

    return distances[target];
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        cerr << "Error: Incorrect number of arguments." << endl;
        return 1;
    }

    string graphFlag = argv[1], graphFilePath = argv[2];
    string dataFlag = argv[3], dataFilePath = argv[4];
    string outputFlag = argv[5], outputFilePath = argv[6];

    if (graphFlag != "-d") {
        cerr << "Error: Unknown flag " << graphFlag << endl;
        return 1;
    }

    Graph graph = readGraphFromFile(graphFilePath);

    if (dataFlag == "-ss" && outputFlag == "-oss") {
        vector<int> sourceNodes = readSourceVertices(dataFilePath);
        double totalExecutionTime = 0.0;

        for (int source : sourceNodes) {
            auto startTime = chrono::high_resolution_clock::now();
            dijkstraAllShortestPaths(graph, source);
            auto endTime = chrono::high_resolution_clock::now();
            totalExecutionTime += chrono::duration<double>(endTime - startTime).count();
        }

        double averageExecutionTime = totalExecutionTime / sourceNodes.size();
        writeSourceResults(outputFilePath, graphFilePath, dataFilePath, "dijkstra", graph, graph.minEdgeWeight, graph.maxEdgeWeight, averageExecutionTime);

    } else if (dataFlag == "-p2p" && outputFlag == "-op2p") {
        vector<pair<int, int>> nodePairs = readVertexPairs(dataFilePath);
        vector<tuple<int, int, int>> results;

        for (const auto& [source, target] : nodePairs) {
            int pathLength = dijkstraShortestPathLength(graph, source, target);
            results.emplace_back(source, target, pathLength);
        }

        writeVertexPairResults(outputFilePath, graphFilePath, dataFilePath, "dijkstra", graph, graph.minEdgeWeight, graph.maxEdgeWeight, results);

    } else {
        cerr << "Error: Unknown flags " << dataFlag << " or " << outputFlag << endl;
        return 1;
    }

    return 0;
}
