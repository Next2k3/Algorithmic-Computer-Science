import java.util.*;
import java.io.FileWriter;
import java.io.IOException;

public class MainToGenerate {
    public static void main(String[] args) {
        for (int n = 10; n < 1001; n += 10) {
            System.out.println(n);
            Graph graph = new Graph(n);

            PrimsMST primMST = new PrimsMST(graph);

            int[][] primMatrix = new int[n][n];

            for (int i = 0; i < n; i++) {
                for (Edge edge : primMST.edges()) {
                    int src = edge.getSrc();
                    int dest = edge.getDest();
                    primMatrix[src][dest] = 1;
                    primMatrix[dest][src] = 1;
                }
            }

            for (int root = 0; root < n; root = root + n/10) {
                int[] rounds = minimizeRounds(primMatrix, n, root);
                int maxRound = 0;
                for (int i = 0; i < n; i++) {
                    if (rounds[i] > maxRound) maxRound = rounds[i];
                }
                try (FileWriter writer = new FileWriter("mst_results2.txt", true)) {
                    writer.write(n + " " + maxRound + "\n");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static int[] minimizeRounds(int[][] mst, int n, int root) {
        List<List<Integer>> adjList = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            adjList.add(new ArrayList<>());
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (mst[i][j] == 1) {
                    adjList.get(i).add(j);
                }
            }
        }

        int[] rounds = new int[n];
        Arrays.fill(rounds, -1);
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(root);
        rounds[root] = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int u = queue.poll();
                
                List<Integer> children = adjList.get(u);
                children.sort((a, b) -> adjList.get(b).size() - adjList.get(a).size());
                int r = rounds[u] + 1;

                for (int v : children) {
                    if (rounds[v] == -1) {
                        rounds[v] = r;
                        queue.offer(v);
                        r++;
                    }
                }
            }
        }

        return rounds;
    }
}
