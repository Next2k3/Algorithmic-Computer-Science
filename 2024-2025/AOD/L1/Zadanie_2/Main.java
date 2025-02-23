import java.io.File;
import java.io.FileNotFoundException;
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

        // Wykonanie sortowania topologicznego
        graph.topologicalSort();
        
        long endTime = System.nanoTime();
        long duration = (endTime - startTime);
        
        System.out.println("Czas wykonania: " + duration + " nanosekund");
    }
}
