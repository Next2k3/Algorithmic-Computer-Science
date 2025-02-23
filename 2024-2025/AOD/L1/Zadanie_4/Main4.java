import java.io.*;
import java.util.*;

public class Main4 {
    public static void main(String[] args) {
        try {
            if (args.length < 1) {
                System.err.println("Usage: java Main4 <input-file>");
                System.exit(1);
            }
            String path = args[0];
            Graph graph = new Graph(path);

            BipartiteChecker checker = new BipartiteChecker(graph);
            long startTime = System.nanoTime();
            boolean isBipartite = checker.isBipartite();
            long endTime = System.nanoTime();
            if (isBipartite) {
                System.out.println("The graph is bipartite.");
                if (graph.getVerticesNum() <= 200){
                    checker.printSubsets();
                }
            } else {
                System.out.println("The graph is not bipartite.");
            }

            System.out.println("\nDuration: " + (endTime - startTime) + " ns");

        } catch (IOException e) {
            System.err.println("Error while trying to load file: " + e.getMessage());
        }
    }
}