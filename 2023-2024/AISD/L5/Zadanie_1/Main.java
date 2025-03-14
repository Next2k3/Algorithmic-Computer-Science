import java.util.HashSet;
import java.util.List;
import java.util.Set;

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

        KruskalsMST kruskalMST = new KruskalsMST(graph);
        System.out.println("Minimum Spanning Tree (MST) edges using Kruskal's Algorithm:");
        for (Edge edge : kruskalMST.edges()) {
            System.out.println(edge);
        }

        double[][] kruskalMatrix = new double[n][n];

        for (int i = 0; i < n; i++) {
            for (Edge edge : kruskalMST.edges()) {
                int src = edge.getSrc();
                int dest = edge.getDest();
                double weight = edge.getWeight();
                kruskalMatrix[src][dest] = weight;
                kruskalMatrix[dest][src] = weight;
            }
        }

        System.out.println();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.printf("%.2f ", kruskalMatrix[i][j]);
            }
            System.out.println();
        }

        System.out.printf("\nTotal weight of MST using Kruskal's Algorithm: %.2f\n\n", kruskalMST.totalWeight());

        PrimsMST primMST = new PrimsMST(graph);
        System.out.println("Minimum Spanning Tree (MST) edges using Prim's Algorithm:");
        for (Edge edge : primMST.edges()) {
            System.out.println(edge);
        }

        double[][] primMatrix = new double[n][n];

        for (int i = 0; i < n; i++) {
            for (Edge edge : primMST.edges()) {
                int src = edge.getSrc();
                int dest = edge.getDest();
                double weight = edge.getWeight();
                primMatrix[src][dest] = weight;
                primMatrix[dest][src] = weight;
            }
        }

        System.out.println();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.printf("%.2f ", primMatrix[i][j]);
            }
            System.out.println();
        }

        System.out.printf("\nTotal weight of MST using Prim's Algorithm: %.2f\n\n", primMST.totalWeight());

        Set<Edge> kruskalEdges = new HashSet<>();
        for (Edge edge : kruskalMST.edges()) {
            kruskalEdges.add(edge);
        }

        Set<Edge> primEdges = new HashSet<>();
        for (Edge edge : primMST.edges()) {
            primEdges.add(edge);
        }

        if (kruskalEdges.equals(primEdges)) {
            System.out.println("Both algorithms produced the same MST.");
        } else {
            System.out.println("The algorithms produced different MSTs.");
        }
    }
}
