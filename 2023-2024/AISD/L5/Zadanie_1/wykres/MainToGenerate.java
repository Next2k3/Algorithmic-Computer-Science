import java.io.FileWriter;
import java.io.IOException;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class MainToGenerate {
    public static void main(String[] args) {
        for (int n = 10; n <= 1000; n += 10) {
            System.out.println(n);
            for (int k = 0; k < 5; k++) {
                Graph graph = new Graph(n);

                // Algorytm Kruskala
                long startTimeKruskal = System.nanoTime();
                KruskalsMST kruskalMST = new KruskalsMST(graph);
                long endTimeKruskal = System.nanoTime();
                long durationKruskal = endTimeKruskal - startTimeKruskal;

                // Algorytm Prima
                long startTimePrim = System.nanoTime();
                PrimsMST primMST = new PrimsMST(graph);
                long endTimePrim = System.nanoTime();
                long durationPrim = endTimePrim - startTimePrim;

                Set<Edge> primEdges = new HashSet<>();
                for (Edge edge : primMST.edges()) {
                    primEdges.add(edge);
                }

                try (FileWriter writer = new FileWriter("mst_results.txt", true)) {
                    writer.write(n + " " + durationKruskal + " " + durationPrim + "\n");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
