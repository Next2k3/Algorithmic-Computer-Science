import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Graph {
    final List<Edge>[] adjacencyLists;
    private final int v;
    private int e;

    public Graph(int v) {
        this.v = v;
        this.e = 0;
        this.adjacencyLists = (List<Edge>[]) new List[v];

        for (int i = 0; i < v; i++) {
            adjacencyLists[i] = new ArrayList<Edge>();
        }

        Random rand = new Random();

        for (int i = 0; i < v; i++) {
            for (int j = i + 1; j < v; j++) {
                double weight = 0;
                while (weight == 0) {
                    weight = rand.nextDouble();
                }
                Edge edge = new Edge(i, j, weight);
                addEdge(edge);
            }
        }
    }

    public int getNumberOfEdges() {
        return e;
    }

    public int getNumberOfVertices() {
        return v;
    }

    public void addEdge(Edge edge) {
        int v = edge.getSrc();
        int w = edge.getDest();
        adjacencyLists[v].add(edge);
        adjacencyLists[w].add(edge);
        e++;
    }
}
