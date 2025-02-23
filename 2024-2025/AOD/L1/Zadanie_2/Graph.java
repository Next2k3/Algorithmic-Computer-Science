import java.util.*;

class Graph {
    private int n; // liczba wierzchołków
    private boolean directed; // czy graf jest skierowany
    private List<List<Integer>> adjList; // lista sąsiedztwa

    // Konstruktor
    public Graph(int n, boolean directed) {
        this.n = n;
        this.directed = directed;
        adjList = new ArrayList<>(n + 1); // lista o indeksach 1...n
        for (int i = 0; i <= n; i++) {
            adjList.add(new ArrayList<>());
        }
    }

    // Dodawanie krawędzi
    public void addEdge(int u, int v) {
        if (u < 1 || u > n || v < 1 || v > n) {
            throw new IllegalArgumentException("Wierzchołki muszą być w zakresie 1 do " + n);
        }
        adjList.get(u).add(v);
        if (!directed) {
            adjList.get(v).add(u);
        }
    }

    // Algorytm sortowania topologicznego z wykrywaniem cyklu
    public boolean topologicalSort() {
        boolean[] visited = new boolean[n + 1];
        boolean[] onStack = new boolean[n + 1];
        Stack<Integer> stack = new Stack<>();
        boolean hasCycle = false;

        for (int v = 1; v <= n; v++) {
            if (!visited[v]) {
                hasCycle |= dfs(v, visited, onStack, stack);
            }
        }

        if (hasCycle) {
            System.out.println("Graf zawiera skierowany cykl.");
            return false;
        } else {
            System.out.println("Graf jest acykliczny.");
            if(n<=200){
		        System.out.println("Kolejność topologiczna:");
		        while (!stack.isEmpty()) {
		            System.out.print(stack.pop() + " ");
		        }
            }
            System.out.println();
            return true;
        }
    }

    // DFS do wykrywania cyklu
    private boolean dfs(int v, boolean[] visited, boolean[] onStack, Stack<Integer> stack) {
        visited[v] = true;
        onStack[v] = true;

        for (int neighbor : adjList.get(v)) {
            if (!visited[neighbor]) {
                if (dfs(neighbor, visited, onStack, stack)) {
                    return true; // Cykl wykryty
                }
            } else if (onStack[neighbor]) {
                return true; // Cykl wykryty
            }
        }

        onStack[v] = false;
        stack.push(v); // Dodaj wierzchołek do stosu po zakończeniu przeszukiwania
        return false;
    }
}
