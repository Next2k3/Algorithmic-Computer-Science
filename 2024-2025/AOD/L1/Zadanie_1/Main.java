import java.util.*;

public class Main {
    public static void main(String[] args) {
    	long startTime = System.nanoTime();
    	
        Scanner scanner = new Scanner(System.in);

        // Odczytanie grafu
        String flag = scanner.nextLine().trim(); // Flaga D lub U
        boolean directed = flag.equalsIgnoreCase("D");

        int n = scanner.nextInt(); // liczba wierzchołków
        int m = scanner.nextInt(); // liczba krawędzi

        Graph graph = new Graph(n, directed);

        // Odczytanie krawędzi
        for (int i = 0; i < m; i++) {
            int u = scanner.nextInt();
            int v = scanner.nextInt();
            graph.addEdge(u, v);
        }

        // Wybór algorytmu przeszukiwania
        String algorithm = scanner.next().trim();

        // Automatyczny wybór wierzchołka startowego
        int startVertex = 1; // Wybieramy pierwszy wierzchołek jako startowy

        // Wykonanie wybranego algorytmu
        if (algorithm.equalsIgnoreCase("DFS")) {
            graph.dfs(startVertex);
        } else if (algorithm.equalsIgnoreCase("BFS")) {
            graph.bfs(startVertex);
        } else {
            System.out.println("Niepoprawny wybór algorytmu. Wybierz DFS lub BFS.");
        }
        long endTime = System.nanoTime();
        long duration = (endTime - startTime);
        
        System.out.println("Czas wykonania: " + duration + " nanosekund");
    }
}
