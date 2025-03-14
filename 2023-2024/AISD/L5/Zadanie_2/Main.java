public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java Main <number_of_vertices>");
            return;
        }

        int n = 0;
        try {
            n = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("The number of vertices must be an integer.");
            return;
        }

        if (n <= 0) {
            System.out.println("The number of vertices must be a positive integer.");
            return;
        }

        Graph graph = new Graph(n);
        System.out.println("Graph created with " + graph.getNumberOfVertices() + " vertices and " + graph.getNumberOfEdges() + " edges.\n");

        double[][] adjacencyMatrix = new double[n][n];

        for (int i = 0; i < n; i++) {
            for (Edge edge : graph.adjacencyLists[i]) {
                int src = edge.getSrc();
                int dest = edge.getDest();
                double weight = edge.getWeight();
                adjacencyMatrix[src][dest] = weight;
                adjacencyMatrix[dest][src] = weight;
            }
        }

        System.out.println("Adjacency Matrix:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.printf("%.2f ", adjacencyMatrix[i][j]);
            }
            System.out.println();
        }

        System.out.println();

        PrimsMST primMST = new PrimsMST(graph);
        System.out.println("Minimum Spanning Tree (MST) edges");
        for (Edge edge : primMST.edges()) {
            System.out.println(edge);
        }

        int[][] primMatrix = new int[n][n];

        for (int i = 0; i < n; i++) {
            for (Edge edge : primMST.edges()) {
                int src = edge.getSrc();
                int dest = edge.getDest();
                primMatrix[src][dest] = 1;
                primMatrix[dest][src] = 1;
            }
        }
        System.out.println();
        int root = 0;
        int maxRound = ShortestPath.minimizeRounds(primMatrix, n, root);

        System.out.println("Starting vertex: " + root);
        System.out.println("\nMinimum rounds: " + maxRound);
    }
}
