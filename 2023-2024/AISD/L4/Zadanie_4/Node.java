public class Node {
    private static final boolean RED = true;
    private static final boolean BLACK = false;

    public int value;
    public Node left;
    public Node right;
    public Node parent;
    public boolean color;

    public Node(int value) {
        this.value = value;
        this.color = RED;
    }
}
