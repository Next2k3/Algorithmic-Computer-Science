#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <chrono>
#include "Graph.h"

using namespace std;

struct Bucket {
    int minRange;
    int maxRange;
    int bucketWidth;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> container;

    Bucket(int minR, int maxR, int width)
        : minRange(minR), maxRange(maxR), bucketWidth(width) {}
};

pair<vector<int>, vector<int>> radixHeapForAll(const Graph &graph, int source) {
    int n = graph.totalVertices;
    int maxCost = graph.maxEdgeWeight;

    vector<Bucket> buckets;
    vector<int> distances(n + 1, INT32_MAX);
    vector<int> predecessors(n + 1, -1);
    distances[source] = 0;

    int currentMaxRange = 0;
    int currentMinRange = 0;
    int currentWidth = 1;
    int k = 0;


    do {
        buckets.emplace_back(currentMinRange, currentMaxRange, currentWidth);
        k++;
        currentMaxRange = (1 << k) - 1;
        currentMinRange = (1 << (k - 1));
        currentWidth = (1 << (k - 1));
    } while (currentMaxRange < n * maxCost);

    int bucketsSize = buckets.size();

    buckets[0].container.emplace(0, source);
    int currentNonEmptyBucketIndex = 0;

    while (currentNonEmptyBucketIndex < bucketsSize) {
        if (buckets[currentNonEmptyBucketIndex].container.empty()) {
            currentNonEmptyBucketIndex++;
            continue;
        }

        while (!buckets[currentNonEmptyBucketIndex].container.empty()) {
            auto [currentDist, currentNode] = buckets[currentNonEmptyBucketIndex].container.top();
            buckets[currentNonEmptyBucketIndex].container.pop();

            for (const auto &edge : graph.adjacencyList[currentNode]) {
                int neighbor = edge.first;
                int weight = edge.second;
                int newDist = currentDist + weight;

                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;
                    predecessors[neighbor] = currentNode;

                    for (int i = currentNonEmptyBucketIndex; i < bucketsSize; ++i) {
                        if (newDist >= buckets[i].minRange && newDist <= buckets[i].maxRange) {
                            buckets[i].container.emplace(newDist, neighbor);
                            break;
                        }
                    }
                }
            }
        }
        currentNonEmptyBucketIndex++;
    }

    return {distances, predecessors};
}

int radixHeapForPair(const Graph &graph, int source, int target) {
    int n = graph.totalVertices;
    int maxCost = graph.maxEdgeWeight;

    vector<Bucket> buckets;
    vector<int> distances(n + 1, INT32_MAX);
    distances[source] = 0;

    int currentMaxRange = 0;
    int currentMinRange = 0;
    int currentWidth = 1;
    int k = 0;

    do {
        buckets.emplace_back(currentMinRange, currentMaxRange, currentWidth);
        k++;
        currentMaxRange = (1 << k) - 1;
        currentMinRange = (1 << (k - 1));
        currentWidth = (1 << (k - 1));
    } while (currentMaxRange < n * maxCost);

    buckets[0].container.emplace(0, source);
    int currentNonEmptyBucketIndex = 0;

    int bucketsSize = buckets.size();

    while (currentNonEmptyBucketIndex < bucketsSize) {
        if (buckets[currentNonEmptyBucketIndex].container.empty()) {
            currentNonEmptyBucketIndex++;
            continue;
        }

        while (!buckets[currentNonEmptyBucketIndex].container.empty()) {
            auto [currentDist, currentNode] = buckets[currentNonEmptyBucketIndex].container.top();
            buckets[currentNonEmptyBucketIndex].container.pop();

            if (currentNode == target) {
                return currentDist;
            }

            for (const auto &edge : graph.adjacencyList[currentNode]) {
                int neighbor = edge.first;
                int weight = edge.second;
                int newDist = currentDist + weight;

                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;

                    for (int i = currentNonEmptyBucketIndex; i < bucketsSize; ++i) {
                        if (newDist >= buckets[i].minRange && newDist <= buckets[i].maxRange) {
                            buckets[i].container.emplace(newDist, neighbor);
                            break;
                        }
                    }
                }
            }
        }
        currentNonEmptyBucketIndex++;
    }

    return distances[target];
}

int main(int argc, char *argv[]) {
    if (argc < 7) {
        cerr << "Usage: ./radixheap -d <graph_file> -ss <sources_file> -oss <output_file>" << endl;
        return 1;
    }

    string graphPath = argv[2];
    string sourcesPath = argv[4];
    string outputPath = argv[6];

    Graph graph = readGraphFromFile(graphPath);

    vector<int> sources = readSourceVertices(sourcesPath);

    double totalTime = 0.0;
    for (int source : sources) {
        auto start = chrono::high_resolution_clock::now();
        auto result = radixHeapForAll(graph, source);
        auto end = chrono::high_resolution_clock::now();
        totalTime += chrono::duration<double>(end - start).count();
    }

    double averageTime = totalTime / sources.size();

     writeSourceResults(outputPath, graphPath, sourcesPath, "radixheap", graph, graph.minEdgeWeight, graph.maxEdgeWeight, averageTime);

    return 0;
}
