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
        adjList.get(u).add(v);
        if (!directed) {
            adjList.get(v).add(u);
        }
    }

    // DFS - Przeszukiwanie wgłąb
    public void dfs(int start) {
        boolean[] visited = new boolean[n + 1];
        List<Integer> order = new ArrayList<>();
        List<int[]> tree = new ArrayList<>();
        
        dfsVisit(start, -1, visited, order, tree);

        System.out.println("DFS Order: " + order);
        System.out.println("DFS Tree: ");
        printTree(tree);
    }

    private void dfsVisit(int v, int parent, boolean[] visited, List<Integer> order, List<int[]> tree) {
        visited[v] = true;
        order.add(v);
        if (parent != -1) {
            tree.add(new int[]{parent, v});
        }
        for (int neighbor : adjList.get(v)) {
            if (!visited[neighbor]) {
                dfsVisit(neighbor, v, visited, order, tree);
            }
        }
    }

    // BFS - Przeszukiwanie wszerz
    public void bfs(int start) {
        boolean[] visited = new boolean[n + 1];
        List<Integer> order = new ArrayList<>();
        List<int[]> tree = new ArrayList<>();
        
        Queue<Integer> queue = new LinkedList<>();
        visited[start] = true;
        queue.add(start);

        while (!queue.isEmpty()) {
            int v = queue.poll();
            order.add(v);
            for (int neighbor : adjList.get(v)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.add(neighbor);
                    tree.add(new int[]{v, neighbor});
                }
            }
        }

        System.out.println("BFS Order: " + order);
        System.out.println("BFS Tree: ");
        printTree(tree);
    }
    private void printTree(List<int[]> tree) {
        Map<Integer, List<Integer>> adjacencyList = new HashMap<>();
        for (int[] edge : tree) {
            adjacencyList.computeIfAbsent(edge[0], k -> new ArrayList<>()).add(edge[1]);
        }

        // Wydruk drzewa - zaczynamy od korzenia
        if (!tree.isEmpty()) {
            int root = tree.get(0)[0];  // Zakładamy, że korzeń to pierwszy wierzchołek
            int treeHeight = computeHeight(root, adjacencyList);
            printTreeRecursive(root, 0, adjacencyList, new char[treeHeight]);
        }
    }
    private void printTreeRecursive(int node, int depth, Map<Integer, List<Integer>> adjacencyList, char[] trace) {
        for (int i = 0; i < depth; i++) {
            System.out.print((trace[i] == '|' ? "|  " : "   "));
        }
        System.out.println("+- " + node);

        List<Integer> children = adjacencyList.get(node);
        if (children == null) {
            return;
        }

        for (int i = 0; i < children.size(); i++) {
            trace[depth] = (i == children.size() - 1) ? ' ' : '|';  // Ostatnie dziecko nie ma pionowej kreski
            printTreeRecursive(children.get(i), depth + 1, adjacencyList, trace);
        }
    }
    private int computeHeight(int root, Map<Integer, List<Integer>> adjacencyList) {
        if (!adjacencyList.containsKey(root)) {
            return 1;  // Pojedynczy węzeł ma wysokość 1
        }

        int maxHeight = 0;
        for (int child : adjacencyList.get(root)) {
            maxHeight = Math.max(maxHeight, computeHeight(child, adjacencyList));
        }
        return maxHeight + 1;  // Wysokość drzewa to maksymalna głębokość dzieci + 1
    }
   
}
