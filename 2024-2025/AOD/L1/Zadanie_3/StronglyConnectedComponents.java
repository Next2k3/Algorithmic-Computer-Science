import java.util.*;

public class StronglyConnectedComponents {
    private List<List<Integer>> adjList;         // Original adjacency list
    private List<List<Integer>> transposedList;  // Transposed graph adjacency list
    private boolean[] visited;
    private Stack<Integer> finishStack;          // Stack storing vertices in order of finish time of first DFS
    private List<List<Integer>> Components;

    public StronglyConnectedComponents(Graph graph) {
        this.adjList = graph.getAdjacencyList();
        int numVertices = adjList.size();
        this.visited = new boolean[numVertices];
        this.finishStack = new Stack<>();
        this.Components = new ArrayList<>();

        // dfs on original graph
        for (int vertex = 0; vertex < numVertices; vertex++) {
            if (!visited[vertex]) {
                iterativeDFS(vertex);
            }
        }

        transposeGraph();

        Arrays.fill(visited, false);

        while (!finishStack.isEmpty()) {
            int vertex = finishStack.pop();
            if (!visited[vertex]) {
                List<Integer> currentSCC = new ArrayList<>();
                iterativeSecondDFS(vertex, currentSCC);
                Components.add(currentSCC);
            }
        }
    }

    // method for iterative DFS for the first pass to fill the finish stack
    private void iterativeDFS(int start) {
        Stack<Integer> stack = new Stack<>();
        stack.push(start);

        while (!stack.isEmpty()) {
            int vertex = stack.peek();

            if (!visited[vertex]) {
                visited[vertex] = true;
            }

            boolean hasUnvisitedNeighbor = false;
            for (int neighbor : adjList.get(vertex)) {
                if (!visited[neighbor]) {
                    stack.push(neighbor);
                    hasUnvisitedNeighbor = true;
                    break;
                }
            }

            if (!hasUnvisitedNeighbor) {
                stack.pop();
                finishStack.push(vertex);
            }
        }
    }

    // method for transposing the graph
    private void transposeGraph() {
        int numVertices = adjList.size();
        transposedList = new ArrayList<>(numVertices);
        for (int i = 0; i < numVertices; i++) {
            transposedList.add(new ArrayList<>());
        }

        for (int vertex = 0; vertex < numVertices; vertex++) {
            for (int neighbor : adjList.get(vertex)) {
                transposedList.get(neighbor).add(vertex);
            }
        }
    }

    // method for iterative DFS for the second pass on the transposed graph to find SCCs
    private void iterativeSecondDFS(int start, List<Integer> currentSCC) {
        Stack<Integer> stack = new Stack<>();
        stack.push(start);

        while (!stack.isEmpty()) {
            int vertex = stack.pop();

            if (!visited[vertex]) {
                visited[vertex] = true;
                currentSCC.add(vertex);

                for (int neighbor : transposedList.get(vertex)) {
                    if (!visited[neighbor]) {
                        stack.push(neighbor);
                    }
                }
            }
        }
    }

    // method to return the number of strongly connected components
    public int getNumberOfSCCs() {
        return Components.size();
    }

    // method to return the sizes of the strongly connected components
    public List<Integer> getSizesOfSCCs() {
        List<Integer> sizes = new ArrayList<>();
        for (List<Integer> scc : Components) {
            sizes.add(scc.size());
        }
        return sizes;
    }

    // method to print all SCCs
    public void printSCCs() {
        System.out.println("Strongly Connected Components:");
        for (List<Integer> scc : Components) {
            System.out.print("[");
            for (int i = 0; i < scc.size(); i++) {
                System.out.print((scc.get(i) + 1));
                if (i < scc.size() - 1) {
                    System.out.print(", ");
                }
            }
            System.out.println("]");
        }
    }
}
