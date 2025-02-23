#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include "Graph.h"

using namespace std;

Graph::Graph(int k) : k(k), totalVertices(1 << k), edgesCapacities(totalVertices, vector<int>(k, 0)) {
    initializeEdges();
}

void Graph::initializeEdges() {
    random_device rd;
    mt19937 gen(rd());

    for (int i = 0; i < totalVertices; ++i) {
        for (int j = 0; j < k; ++j) {
            int toggled = i ^ (1 << j);
            if (toggled > i) {
                int l = max({hammingWeight(i), k - hammingWeight(i), hammingWeight(toggled), k - hammingWeight(toggled)});
                uniform_int_distribution<> dist(1, 1 << l);
                edgesCapacities[i][j] = dist(gen);
            }
        }
    }
}

int Graph::hammingWeight(int x) const {
    int count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}

pair<int, int> Graph::edmondsKarp() {
    int flow = 0;
    int augmentingPathsCount = 0;

    while (true) {
        vector<int> pred(totalVertices, -1);
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int currentNode = q.front();
            q.pop();

            for (int i = 0; i < k; ++i) {
                int neighborNode = currentNode ^ (1 << i);
                if (pred[neighborNode] == -1 && neighborNode != 0 && edgesCapacities[currentNode][i] > 0) {
                    pred[neighborNode] = currentNode;
                    q.push(neighborNode);
                }
            }
        }

        if (pred[totalVertices - 1] == -1) {
            return {flow, augmentingPathsCount};
        } else {
            ++augmentingPathsCount;
            int flowToIncrease = INT_MAX;
            int currentNode = totalVertices - 1;

            while (currentNode != 0) {
                int previous = pred[currentNode];
                int differingBit = log2(previous ^ currentNode);
                flowToIncrease = min(flowToIncrease, edgesCapacities[previous][differingBit]);
                currentNode = previous;
            }

            currentNode = totalVertices - 1;
            while (currentNode != 0) {
                int previous = pred[currentNode];
                int differingBit = log2(previous ^ currentNode);
                edgesCapacities[previous][differingBit] -= flowToIncrease;
                edgesCapacities[currentNode][differingBit] += flowToIncrease;
                currentNode = previous;
            }

            flow += flowToIncrease;
        }
    }
}

void Graph::printFlowDetails() const {
    cout << "FLOW DETAILS: \n";
    for (int i = 0; i < totalVertices; ++i) {
        for (int j = 0; j < k; ++j) {
            int toggled = i ^ (1 << j);
            if (toggled > i) {
                cout << i << " -> " << toggled << " : " << edgesCapacities[toggled][j] << "\n";
            }
        }
    }
}

int Graph::getTotalVertices() const {
    return totalVertices;
}

int Graph::getEdgeCapacity(int from, int to) const {
    int differingBit = log2(from ^ to);
    if (differingBit < k && (from ^ (1 << differingBit)) == to) {
        return edgesCapacities[from][differingBit];
    } else {
        return 0;
    }
}
