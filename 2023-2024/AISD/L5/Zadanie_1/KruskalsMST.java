import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class KruskalsMST {
    private List<Edge> mst;
    private double totalWeight;

    public KruskalsMST(Graph graph) {
        mst = new ArrayList<>();
        totalWeight = 0.0;

        List<Edge> edges = new ArrayList<>();
        for (int i = 0; i < graph.getNumberOfVertices(); i++) {
            for (Edge edge : graph.adjacencyLists[i]) {
                if (edge.getSrc() < edge.getDest()) {
                    edges.add(edge);
                }
            }
        }

        Collections.sort(edges);

        UnionFind uf = new UnionFind(graph.getNumberOfVertices());

        for (Edge edge : edges) {
            int v = edge.getSrc();
            int w = edge.getDest();

            if (!uf.connected(v, w)) {
                uf.union(v, w);
                mst.add(edge);
                totalWeight += edge.getWeight();
            }
        }
    }

    public Iterable<Edge> edges() {
        return mst;
    }

    public double totalWeight() {
        return totalWeight;
    }

    private class UnionFind {
        private int[] parent;
        private int[] rank;

        public UnionFind(int n) {
            parent = new int[n];
            rank = new int[n];
            for (int i = 0; i < n; i++) {
                parent[i] = i;
                rank[i] = 0;
            }
        }

        public int find(int p) {
            while (p != parent[p]) {
                parent[p] = parent[parent[p]];
                p = parent[p];
            }
            return p;
        }

        public void union(int p, int q) {
            int rootP = find(p);
            int rootQ = find(q);
            if (rootP == rootQ) return;

            if (rank[rootP] < rank[rootQ]) {
                parent[rootP] = rootQ;
            } else if (rank[rootP] > rank[rootQ]) {
                parent[rootQ] = rootP;
            } else {
                parent[rootQ] = rootP;
                rank[rootP]++;
            }
        }

        public boolean connected(int p, int q) {
            return find(p) == find(q);
        }
    }
}
