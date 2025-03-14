import java.util.PriorityQueue;
import java.util.List;
import java.util.ArrayList;
import java.util.Comparator;

public class PrimsMST {
    private boolean[] marked;
    private List<Edge> mst;
    private double totalWeight;
    private PriorityQueue<Edge> pq;

    public PrimsMST(Graph graph) {
        marked = new boolean[graph.getNumberOfVertices()];
        mst = new ArrayList<>();
        totalWeight = 0.0;
        pq = new PriorityQueue<>(Comparator.comparingDouble(Edge::getWeight));

        visit(graph, 0);
        while (!pq.isEmpty() && mst.size() < graph.getNumberOfVertices() - 1) {
            Edge edge = pq.poll();
            int v = edge.getSrc();
            int w = edge.getDest();

            if (marked[v] && marked[w]) continue;

            mst.add(edge);
            totalWeight += edge.getWeight();

            if (!marked[v]) visit(graph, v);
            if (!marked[w]) visit(graph, w);
        }
    }

    private void visit(Graph graph, int vertex) {
        marked[vertex] = true;
        for (Edge edge : graph.adjacencyLists[vertex]) {
            if (!marked[edge.getOtherVertex(vertex)]) {
                pq.offer(edge);
            }
        }
    }

    public Iterable<Edge> edges() {
        return mst;
    }

    public double totalWeight() {
        return totalWeight;
    }
}
