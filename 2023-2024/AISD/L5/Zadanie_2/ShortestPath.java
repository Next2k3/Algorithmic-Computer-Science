import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class ShortestPath {

    public static int minimizeRounds(int[][] adjMatrix, int n, int root) {
        Node[] nodes = new Node[n];

        for (int i = 0; i < n; i++) {
            nodes[i] = new Node(i);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (adjMatrix[i][j] == 1) {
                    nodes[i].addChild(nodes[j]);
                }
            }
        }

        setParentChildRelations(nodes, root, null);

        int maxRound = computePropagationOrder(nodes[root], null);

        return maxRound;
    }

    private static void setParentChildRelations(Node[] nodes, int current, Node parent) {
        nodes[current].setParent(parent);

        for (Node child : nodes[current].getChildren()) {
            if (child != parent) {
                setParentChildRelations(nodes, child.getId(), nodes[current]);
            }
        }
    }

    private static int computePropagationOrder(Node node, Node parent) {
        if (node.getChildren().size() == 0 || (node.getChildren().size() == 1 && node.getChildren().get(0) == parent)) {
            return 0;
        }

        List<Pair<Integer, Node>> childrenRounds = new ArrayList<>();

        for (Node child : node.getChildren()) {
            if (child != parent) {
                int childRound = computePropagationOrder(child, node);
                childrenRounds.add(new Pair<>(childRound, child));
            }
        }

        Collections.sort(childrenRounds, (a, b) -> b.getKey() - a.getKey());

        int maxRound = 0;
        int currentRound = 1;

        System.out.printf("Node: " + node.getId() + " -> Child Node: ");

        for (Pair<Integer, Node> pair : childrenRounds) { 
            Node childNode = pair.getValue();
            System.out.printf(childNode.getId() +", ");
            int childRound = pair.getKey();
            maxRound = Math.max(maxRound, currentRound + childRound);
        }
        System.out.println();

        return maxRound;
    }
}
