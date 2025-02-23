#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include <stdexcept>
#include <tuple>
#include <climits>
#include <cstdint>

using namespace std;

struct Graph {
    int totalVertices;
    int totalEdges;
    vector<vector<pair<int, int>>> adjacencyList;
    int minEdgeWeight;
    int maxEdgeWeight;

    Graph(int vertices, int edges, int minWeight, int maxWeight, vector<vector<pair<int, int>>> adjacencyList)
        : totalVertices(vertices), totalEdges(edges), minEdgeWeight(minWeight), maxEdgeWeight(maxWeight),
          adjacencyList(adjacencyList) {}
};

Graph readGraphFromFile(const string& filename) {
    int totalVertices = 0, totalEdges = 0;
    int minEdgeWeight = INT32_MAX;
    int maxEdgeWeight = INT32_MIN;
    vector<vector<pair<int, int>>> adjacencyList;

    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string flag;
        iss >> flag;

        if (flag == "c") {
            continue;
        } else if (flag == "p") {
            string temp;
            iss >> temp >> totalVertices >> totalEdges;
            adjacencyList.resize(totalVertices + 1);
        } else if (flag == "a") {
            int u, v, c;
            iss >> u >> v >> c;
            maxEdgeWeight = max(maxEdgeWeight, c);
            minEdgeWeight = min(minEdgeWeight, c);
            adjacencyList[u].emplace_back(v, c);
        } else {
            throw runtime_error("Unknown flag in file at line: " + line);
        }
    }

    file.close();
    return Graph(totalVertices, totalEdges, minEdgeWeight, maxEdgeWeight, adjacencyList);
}

vector<int> readSourceVertices(const string& filename) {
    vector<int> sourceVertices;
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string flag;
        iss >> flag;

        if (flag == "c") {
            continue;
        } else if (flag == "p") {
            continue;
        } else if (flag == "s") {
            int vertex;
            iss >> vertex;
            sourceVertices.push_back(vertex);
        } else {
            throw runtime_error("Unknown flag in file at line: " + line);
        }
    }

    file.close();
    return sourceVertices;
}

vector<pair<int, int>> readVertexPairs(const string& filename) {
    vector<pair<int, int>> vertexPairs;
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string flag;
        iss >> flag;

        if (flag == "c") {
            continue;
        } else if (flag == "p") {
            continue;
        } else if (flag == "q") {
            int u, v;
            iss >> u >> v;
            vertexPairs.emplace_back(u, v);
        } else {
            throw runtime_error("Unknown flag in file at line: " + line);
        }
    }

    file.close();
    return vertexPairs;
}

void writeSourceResults(const string& outputFilename, const string& graphFilename, const string& sourceFilename, const string& algorithmType, const Graph& graph, int minWeight, int maxWeight, double avgTime) {
    ofstream file(outputFilename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + outputFilename);
    }

    file << "p res sp ss " << algorithmType << "\n";
    file << "-------------------------------\n";
    file << "f " << graphFilename << " " << sourceFilename << "\n";
    file << "g " << graph.totalVertices << " " << graph.totalEdges << " " << minWeight << " " << maxWeight << "\n";
    file << "t " << avgTime << "\n";

    file.close();
}

void writeVertexPairResults(const string& outputFilename, const string& graphFilename, const string& pairsFilename, const string& algorithmType, const Graph& graph, int minWeight, int maxWeight, const vector<tuple<int, int, int>>& vertexPairsWithResults) {
    ofstream file(outputFilename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + outputFilename);
    }

    file << "p res sp p2p " << algorithmType << "\n";
    file << "c -------------------------------\n";
    file << "f " << graphFilename << " " << pairsFilename << "\n";
    file << "g " << graph.totalVertices << " " << graph.totalEdges << " " << minWeight << " " << maxWeight << "\n";

    for (const auto& pair : vertexPairsWithResults) {
        int u = get<0>(pair);
        int v = get<1>(pair);
        int cost = get<2>(pair);

        if (cost == INT32_MAX) {
            file << "d " << u << " " << v << " INFINITY\n";
        } else {
            file << "d " << u << " " << v << " " << cost << "\n";
        }
    }

    file.close();
}
