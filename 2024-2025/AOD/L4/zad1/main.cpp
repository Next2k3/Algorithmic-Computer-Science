#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Error: insufficient arguments.\n";
        return 1;
    }

    string option = argv[1];
    if (option == "--size" && argc >= 3) {
        int k = stoi(argv[2]);


        Graph graph(k);
        Graph graphCopy = graph;
        cout << "Generated hypercube of size " << k << endl;

        auto start = chrono::high_resolution_clock::now();
        auto [maxFlow, augmentingPaths] = graph.edmondsKarp();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        cout << "Maximum flow: " << maxFlow << endl;
        cout << "Augmenting paths count: " << augmentingPaths << endl;
        
        cout<<argc<< " "<<string(argv[3])<<endl;
        if (argc >= 4 && string(argv[3]) == "--printFlow") {
            graph.printFlowDetails();
        }
        if (argc >= 4 && (string(argv[3]) == "--JuMP" || (argc >= 5 && string(argv[4]) == "--JuMP"))) {
            string filename = "zad1_LP.jl";
            if (string(argv[3]) == "--JuMP"){
                filename = argv[4];
            }
            else if (string(argv[4]) == "--JuMP"){
                filename = argv[5];
            }

            ofstream outFile(filename);
            if (!outFile) {
                cerr << "Error: Unable to open file for writing Julia script.\n";
                return 1;
            }

            outFile << "using JuMP\n";
            outFile << "import GLPK\n";
            outFile << "G = zeros(Int," << graphCopy.getTotalVertices() << "," << graphCopy.getTotalVertices() << ")\n\n";
            outFile << "# Matrix of capacities of graph G: \n";

            for (int i = 1; i <= graphCopy.getTotalVertices(); ++i) {
                outFile << "G[" << i << ", :] = [";
                for (int j = 1; j <= graphCopy.getTotalVertices(); ++j) {
                    if (i != j && ceil(log2((i - 1) ^ (j - 1))) == floor(log2((i - 1) ^ (j - 1)))) {
                        outFile << graphCopy.getEdgeCapacity(i - 1, j - 1);
                    } else {
                        outFile << "0";
                    }
                    outFile << " ";
                }
                outFile << "]\n";
            }

            outFile << "\n";
            outFile << "n = size(G)[1]\n";
            outFile << "max_flow = Model(GLPK.Optimizer)\n";
            outFile << "set_silent(max_flow)\n";
            outFile << "@variable(max_flow, f[1:n, 1:n] >= 0)\n\n";

            outFile << "#Forcing zeros where edge does not exist: \n";
            outFile << "for i in 1:n, j in 1:n\n";
            outFile << "  if G[i,j] == 0\n";
            outFile << "    fix(f[i,j], 0.0; force = true)\n";
            outFile << "  end\n";
            outFile << "end\n\n";

            outFile << "# constraint - cannot overflow an edge\n";
            outFile << "@constraint(max_flow, [i = 1:n, j = 1:n], f[i, j] <= G[i, j])\n\n";

            outFile << "# constraint - from each vertex input flow must equal output flow\n";
            outFile << "@constraint(max_flow, [i = 1:n; i != 1 && i != " << graphCopy.getTotalVertices() << "], sum(f[i, :]) == sum(f[:, i]))\n\n";

            outFile << "# objective - looking for maximum flow from source\n";
            outFile << "@objective(max_flow, Max, sum(f[1, :]))\n\n";

            outFile << "optimize!(max_flow)\n\n";

            outFile << "print(\"Maximum flow: \")\n";
            outFile << "println(objective_value(max_flow))\n\n";

            outFile << "print(\"FLOW DETAILS: \\n\")\n";
            outFile << "for i in 1:n\n";
            outFile << "  for j in 1:" << k << "\n";
            outFile << "    toggled = (i-1) ⊻ 2^(j-1)\n";
            outFile << "    edgeCapacity = 0\n";
            outFile << "    if (toggled > i-1)\n";
            outFile << "      edgeCapacity = value(f[i, toggled+1])\n";
            outFile << "      print(i-1, \" -> \", toggled, \" : \", edgeCapacity, \"\\n\")\n";
            outFile << "    end\n";
            outFile << "  end\n";
            outFile << "end\n";
            outFile << "print(\"Execution time: \")\n";
            outFile << "println(solve_time(max_flow))\n";

            outFile.close();
            cout << "Julia script saved to " << filename << endl;
        }

        cerr << "Execution time: " << elapsed.count() << "s" << endl;

    } else if (option == "--tests") {
        ofstream outFile("testResults.txt");
        if (!outFile) {
            cerr << "Error: Unable to open file for writing test results.\n";
            return 1;
        }

        for (int k = 1; k <= 16; k++) {
            cout << k << endl;
            double totalTime = 0.0;
            long long totalFlow = 0;
            long long totalAugmentingPaths = 0;

            int counts = 20;
            for (int i = 0; i < counts; ++i) {

                Graph graph(k);
                auto start = chrono::high_resolution_clock::now();
                auto [flow, pathsCount] = graph.edmondsKarp();
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double> elapsed = end - start;

                totalTime += elapsed.count();
                totalFlow += flow;
                totalAugmentingPaths += pathsCount;
            }

            outFile << k << " " << totalFlow / counts << " " << totalAugmentingPaths / counts << " " << totalTime / counts << "\n";
        }
        outFile.close();

    } else {
        cerr << "Error: Invalid arguments\n";
        return 1;
    }

    return 0;
}
