import java.util.*;

public class BipartiteChecker {
    private List<List<Integer>> adjList;
    private int[] color;
    private boolean isBipartite;

    // constructor for bipartite checker
    public BipartiteChecker(Graph graph) {
        List<List<Integer>> adjList = graph.getAdjacencyList();
        for (int u = 0; u < adjList.size(); u++) {
            for (int v : adjList.get(u)) {
                if (!adjList.get(v).contains(u)) {  // Check if the reverse edge already exists
                    adjList.get(v).add(u);  // Add reverse edge
                }
            }
        }
        this.adjList = adjList;
    }

    // method to check if the graph is bipartite
    public boolean isBipartite() {
        int numVertices = adjList.size();
        this.color = new int[numVertices];
        Arrays.fill(color, -1);

        // processing all components in case grphf is disconnected
        for (int i = 0; i < numVertices; i++) {
            if (color[i] == -1) {  // If the vertex is uncolored, start BFS
                if (!bipartiteBFS(i, color)) {
                    isBipartite = false;
                    return false;  // if any component is not bipartite, whole graph is not bipartite
                }
            }
        }
        isBipartite = true;
        return true;
    }

    // helper method to perform BFS and check bipartiteness
    private boolean bipartiteBFS(int start, int[] color) {
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(start);
        color[start] = 0;

        while (!queue.isEmpty()) {
            int vertex = queue.poll();

            for (int neighbor : adjList.get(vertex)) {
                if (color[neighbor] == -1) {
                    color[neighbor] = 1 - color[vertex];
                    queue.offer(neighbor);
                } else if (color[neighbor] == color[vertex]) {
                    return false;  // If the neighbor has the same color as vertex graph is not bipartite
                }
            }
        }
        return true;
    }

    // method for printing the subsets if graph is bipartite
    public void printSubsets() {
        List<Integer> color0 = new ArrayList<>();
        List<Integer> color1 = new ArrayList<>();
        if (!isBipartite) {
            System.out.println("Graph is not bipartite");
        }
        else {
            for (int i = 0; i < adjList.size(); i++) {
                if (color[i] == 0) {
                    color0.add(i + 1);
                }
                else if (color[i] == 1) {
                    color1.add(i + 1);
                }
            }
            System.out.println(color0);
            System.out.println(color1);
        }
    }
}