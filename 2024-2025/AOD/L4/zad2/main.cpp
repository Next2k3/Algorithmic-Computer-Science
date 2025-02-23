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
    if (option == "--size" && argc >= 5) {
        int k = stoi(argv[2]);
        int degree = stoi(argv[4]);

        BipartiteGraph graph(k, degree);
        BipartiteGraph graphCopy = graph;
        cout << "Generated bipartite graph with |V1| = 2^" << k << ", |V2| = 2^" << k << ", degree = " << degree << endl;

        auto start = chrono::high_resolution_clock::now();
        auto flow = graph.getMaxFlow();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;

        cout << "Maximum matching: " << flow << endl;

        if (argc >= 6 && string(argv[5]) == "--printMatching") {
            graph.printMatching();
        }

        if ((argc >= 6 && string(argv[5]) == "--JuMP") || ( argc >= 7 && string(argv[6]) == "--JuMP")) {
            string filename = "zad2_LP.jl";
            if (string(argv[5]) == "--JuMP"){
                filename = argv[6];
            }
            else if (string(argv[6]) == "--JuMP"){
                filename = argv[7];
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

            for (int i = 0; i < graphCopy.getTotalVertices(); i++) {
                outFile << "G[" << i + 1 << ", :] = [";
                for (int j = 0; j < graphCopy.getTotalVertices(); j++) {
                    if (j >= i){
                        outFile << graph.getEdgeCapacity(i, j) << " ";
                    }
                    else {
                        outFile << 0 << " ";
                    }
                    
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

            outFile << "print(\"Maximal matching: \")\n";
            outFile << "println(objective_value(max_flow))\n\n";

            outFile << "println(\"Matching details:\")\n";
            outFile << "for i in 2:n-1\n";
            outFile << "  for j in 2:n-1\n";
            outFile << "    if value(f[i, j]) > 0\n";
            outFile << "      println(i-1, \" -> \", j-1)\n";
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

        for (int k = 3; k <= 10; k++) {
            cout << k << endl;
            for (int degree = 1; degree <= k; ++degree) {
                double totalTime = 0.0;
                long long totalMatching = 0;

                int counts = 20;
                for (int i = 0; i < counts; i++) {
                    BipartiteGraph graph(k, degree);
                    auto start = chrono::high_resolution_clock::now();
                    auto flow = graph.getMaxFlow();
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> elapsed = end - start;
                    
                    totalTime += elapsed.count();
                    totalMatching += flow;
                }

                outFile << k << " " << degree << " " << totalMatching / counts << " " << totalTime / counts << "\n";
            }
        }
        outFile.close();
    } else {
        cerr << "Error: Invalid arguments\n";
        return 1;
    }

    return 0;
}
