public class Edge implements Comparable<Edge> {
    private final int src, dest;
    private final double weight;

    public Edge(int src, int dest, double weight) {
        this.src = src;
        this.dest = dest;
        this.weight = weight;
    }

    public int getSrc() {
        return src;
    }

    public int getDest() {
        return dest;
    }

    public double getWeight() {
        return weight;
    }

    public int getOtherVertex(int vertex) {
        if (vertex == src) {
            return dest;
        } else if (vertex == dest) {
            return src;
        } else {
            throw new IllegalArgumentException("Invalid vertex");
        }
    }

    @Override
    public int compareTo(Edge other) {
        return Double.compare(this.weight, other.weight);
    }

    @Override
    public String toString() {
        return String.format("(%d, %d, %.2f)", src, dest, weight);
    }
}
