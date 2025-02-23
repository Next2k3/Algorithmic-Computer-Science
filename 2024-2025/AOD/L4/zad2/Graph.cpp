#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <limits>
#include <random>
#include "Graph.h"

using namespace std;

BipartiteGraph::BipartiteGraph(int k, int degree) {
    int v1 = 1 << k;
    int v2 = 1 << k;
    totalVertices = v1 + v2 + 2;
    source = 0;
    sink = totalVertices - 1;
    adjList.resize(totalVertices);

    for (int i = 1; i <= v1; i++) {
        addEdge(source, i, 1);
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, v2);
    
    for (int i = 1; i <= v1; i++) {
        for (int j = 0; j < degree; j++) {
            int neighbor = dis(gen) + v1;
            addEdge(i, neighbor, 1);
        }
    }

    for (int i = v1 + 1; i <= v1 + v2; i++) {
        addEdge(i, sink, 1);
    }
}

void BipartiteGraph::addEdge(int from, int to, int capacity) {
    adjList[from].push_back({to, capacity, 0});
    adjList[to].push_back({from, 0, 0});
}

bool BipartiteGraph::bfs() {
    pred.assign(totalVertices, -1);
    queue<int> q;
    q.push(source);
    pred[source] = source;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (auto& edge : adjList[current]) {
            if (pred[edge.to] == -1 && edge.capacity - edge.flow > 0) {
                pred[edge.to] = current;
                if (edge.to == sink) return true;
                q.push(edge.to);
            }
        }
    }
    return false;
}

int BipartiteGraph::getMaxFlow() {
    int maxFlow = 0;

    while (bfs()) {
        int flow = numeric_limits<int>::max();

        for (int current = sink; current != source; current = pred[current]) {
            int prev = pred[current];
            for (auto& edge : adjList[prev]) {
                if (edge.to == current) {
                    flow = min(flow, edge.capacity - edge.flow);
                }
            }
        }

        for (int current = sink; current != source; current = pred[current]) {
            int prev = pred[current];
            for (auto& edge : adjList[prev]) {
                if (edge.to == current) {
                    edge.flow += flow;
                }
            }
            for (auto& edge : adjList[current]) {
                if (edge.to == prev) {
                    edge.flow -= flow;
                }
            }
        }

        maxFlow += flow;
    }

    return maxFlow;
}

void BipartiteGraph::printMatching() const {
    cout << "Matching edges:" << endl;
    for (int i = 1; i < (totalVertices - 2) / 2 + 1; i++) {
        for (const auto& edge : adjList[i]) {
            if (edge.to > (totalVertices - 2) / 2 && edge.to < sink && edge.flow > 0) {
                cout << i << " -> " << edge.to << endl;
            }
        }
    }
}

int BipartiteGraph::getTotalVertices() const {
    return totalVertices;
}

int BipartiteGraph::getEdgeCapacity(int from, int to) const {
    for (const auto& edge : adjList[from]) {
        if (edge.to == to) {
            return 1;
        }
    }
    return 0;
}
