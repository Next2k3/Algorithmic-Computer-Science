#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <chrono>
#include "Graph.h"
#include <deque>
#include <unordered_map>
#include <algorithm>

using namespace std;

pair<vector<int>, vector<int>> dialShortestPaths(const Graph& graph, int source) {
    int n = graph.totalVertices;
    int maxCost = graph.maxEdgeWeight;
    vector<int> d(n + 1, INT32_MAX);
    vector<int> pred(n + 1, -1);

    d[source] = 0;

    vector<list<int>> buckets(maxCost + 1);
    int currentBucket = 0;
    int emptyBucketsInRow = 0;

    buckets[currentBucket].push_back(source);

    while (emptyBucketsInRow < maxCost + 1) {
        if (buckets[currentBucket].empty()) {
            currentBucket = (currentBucket + 1) % (maxCost + 1);
            emptyBucketsInRow++;
        } else {
            emptyBucketsInRow = 0;
            while (!buckets[currentBucket].empty()) {
                int node = buckets[currentBucket].front();
                buckets[currentBucket].pop_front();

                for (const auto& neighborEdge : graph.adjacencyList[node]) {
                    int neighbor = neighborEdge.first;
                    int cost = neighborEdge.second;
                    int value = d[node] + cost;

                    if (d[neighbor] > value) {
                        if (d[neighbor] != INT32_MAX) {
                            buckets[d[neighbor] % (maxCost + 1)].remove(neighbor);
                        }
                        d[neighbor] = value;
                        pred[neighbor] = node;
                        buckets[value % (maxCost + 1)].push_back(neighbor);
                    }
                }
            }
        }
    }

    return {d, pred};
}

int dialShortestPathLength(const Graph& graph, int source, int target) {
    int vertexCount = graph.totalVertices;
    int maxEdgeCost = graph.maxEdgeWeight;
    vector<int> distances(vertexCount + 1, INT32_MAX);

    distances[source] = 0;

    vector<list<int>> buckets(maxEdgeCost + 1);
    int currentBucketIndex = 0, consecutiveEmptyBuckets = 0;

    buckets[currentBucketIndex].push_back(source);

    while (consecutiveEmptyBuckets <= maxEdgeCost) {
        if (buckets[currentBucketIndex].empty()) {
            currentBucketIndex = (currentBucketIndex + 1) % (maxEdgeCost + 1);
            ++consecutiveEmptyBuckets;
        } else {
            consecutiveEmptyBuckets = 0;
            while (!buckets[currentBucketIndex].empty()) {
                int currentNode = buckets[currentBucketIndex].front();
                buckets[currentBucketIndex].pop_front();

                if (currentNode == target) {
                    return distances[currentNode];
                }

                for (const auto& [neighbor, edgeCost] : graph.adjacencyList[currentNode]) {
                    int newDistance = distances[currentNode] + edgeCost;
                    if (distances[neighbor] > newDistance) {
                        if (distances[neighbor] != INT32_MAX) {
                            buckets[distances[neighbor] % (maxEdgeCost + 1)].remove(neighbor);
                        }
                        distances[neighbor] = newDistance;
                        buckets[newDistance % (maxEdgeCost + 1)].push_back(neighbor);
                    }
                }
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
            dialShortestPaths(graph, source);
            auto endTime = chrono::high_resolution_clock::now();
            totalExecutionTime += chrono::duration<double>(endTime - startTime).count();
        }

        double averageExecutionTime = totalExecutionTime / sourceNodes.size();
        writeSourceResults(outputFilePath, graphFilePath, dataFilePath, "dial", graph, graph.minEdgeWeight, graph.maxEdgeWeight, averageExecutionTime);

    } else if (dataFlag == "-p2p" && outputFlag == "-op2p") {
        vector<pair<int, int>> nodePairs = readVertexPairs(dataFilePath);
        vector<tuple<int, int, int>> results;

        for (const auto& [source, target] : nodePairs) {
            int pathLength = dialShortestPathLength(graph, source, target);
            results.emplace_back(source, target, pathLength);
        }

        writeVertexPairResults(outputFilePath, graphFilePath, dataFilePath, "dial", graph, graph.minEdgeWeight, graph.maxEdgeWeight, results);

    } else {
        cerr << "Error: Unknown flags " << dataFlag << " or " << outputFlag << endl;
        return 1;
    }

    return 0;
}
