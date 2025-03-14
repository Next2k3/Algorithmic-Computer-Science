import java.util.ArrayList;
import java.util.List;

class Node {
    private int id;
    private List<Node> children;
    private Node parent;

    public Node(int id) {
        this.id = id;
        this.children = new ArrayList<>();
    }

    public int getId() {
        return id;
    }

    public List<Node> getChildren() {
        return children;
    }

    public void addChild(Node child) {
        children.add(child);
    }

    public void setParent(Node parent) {
        this.parent = parent;
    }

    public Node getParent() {
        return parent;
    }

    public int minimizeRound(Node parent) {
        if (children.size() == 0 || (children.size() == 1 && children.get(0) == parent)) {
            return 0;
        }
        
        List<Pair<Integer, Node>> pairs = new ArrayList<>();

        for (Node child : children) {
            if (child == parent) continue;
            pairs.add(new Pair<>(child.minimizeRound(this), child));
        }

        pairs.sort((a, b) -> b.getKey() - a.getKey());

        int maxRound = 0;
        int currentRound = 1;
        
        for (Pair<Integer, Node> pair : pairs) {
            int childRound = pair.getKey() + currentRound;
            maxRound = Math.max(maxRound, childRound);
            currentRound++;
        }

        return maxRound;
    }
}
