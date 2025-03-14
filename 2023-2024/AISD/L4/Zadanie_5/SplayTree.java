import java.util.LinkedList;
import java.util.Queue;

public class SplayTree {
    private Node root;

    public SplayTree() {
        root = null;
    }

    public void insert(int value) {
        Node addedNode = new Node(value);
        insert(addedNode);
        System.out.println(value + " added to tree");
    }

    public void insert(Node z) {
        Node x = root;
        Node y = null;

        while (x != null) {
            y = x;
            if (x.value < z.value) {
                x = x.right;
            } else {
                x = x.left;
            }
        }

        x = z;
        x.parent = y;
        if (y == null) {
            root = x;
        } else if (y.value < x.value) {
            y.right = x;
        } else {
            y.left = x;
        }

        splay(x);
    }

    public void delete(int value) {
        Node nodeToDelete = findNode(root, value);
        if (nodeToDelete != null) {
            delete(nodeToDelete);
            System.out.println(value + " deleted from tree");
        } else {
            System.out.println(value + " not found in tree");
        }
    }

    public void delete(Node z) {
        if (z == null) {
            return;
        }
        splay(z);

        if (z.left == null) {
            transplant(z, z.right);
        } else if (z.right == null) {
            transplant(z, z.left);
        } else {
            Node y = treeMinimum(z.right);
            if (y.parent != z) {
                transplant(y, y.right);
                y.right = z.right;
                y.right.parent = y;
            }
            transplant(z, y);
            y.left = z.left;
            y.left.parent = y;
        }
    }

    private Node findNode(Node root, int value) {
        Node current = root;
        while (current != null && current.value != value) {
            if (value < current.value) {
                current = current.left;
            } else {
                current = current.right;
            }
        }
        return current;
    }

    private void transplant(Node u, Node v) {
        if (u.parent == null) {
            root = v;
        } else if (u == u.parent.left) {
            u.parent.left = v;
        } else {
            u.parent.right = v;
        }
        if (v != null) {
            v.parent = u.parent;
        }
    }

    private Node treeMinimum(Node x) {
        while (x.left != null) {
            x = x.left;
        }
        return x;
    }

    private void leftRotate(Node x) {
        Node y = x.right;
        if (y != null) {
            x.right = y.left;
            if (y.left != null) y.left.parent = x;
            y.parent = x.parent;
        }
        if (x.parent == null) root = y;
        else if (x == x.parent.left) x.parent.left = y;
        else x.parent.right = y;
        if (y != null) y.left = x;
        x.parent = y;
    }

    private void rightRotate(Node x) {
        Node y = x.left;
        if (y != null) {
            x.left = y.right;
            if (y.right != null) y.right.parent = x;
            y.parent = x.parent;
        }
        if (x.parent == null) root = y;
        else if (x == x.parent.left) x.parent.left = y;
        else x.parent.right = y;
        if (y != null) y.right = x;
        x.parent = y;
    }

    private void splay(Node x) {
        while (x.parent != null) {
            if (x.parent.parent == null) {
                if (x.parent.left == x) rightRotate(x.parent);
                else leftRotate(x.parent);
            } else if (x.parent.left == x && x.parent.parent.left == x.parent) {
                rightRotate(x.parent.parent);
                rightRotate(x.parent);
            } else if (x.parent.right == x && x.parent.parent.right == x.parent) {
                leftRotate(x.parent.parent);
                leftRotate(x.parent);
            } else if (x.parent.left == x && x.parent.parent.right == x.parent) {
                rightRotate(x.parent);
                leftRotate(x.parent);
            } else {
                leftRotate(x.parent);
                rightRotate(x.parent);
            }
        }
    }

    public void printTree() {
        int height = height();
        char[] leftTrace = new char[height];
        char[] rightTrace = new char[height];
        printTreeRecursive(root, 0, '-', leftTrace, rightTrace);
    }

    private void printTreeRecursive(Node node, int depth, char prefix, char[] leftTrace, char[] rightTrace) {
        if (node == null) {
            return;
        }

        if (node.left != null) {
            printTreeRecursive(node.left, depth + 1, '/', leftTrace, rightTrace);
        }

        if (prefix == '/') {
            leftTrace[depth - 1] = '|';
        }
        if (prefix == '\\') {
            rightTrace[depth - 1] = ' ';
        }
        if (depth == 0) {
            System.out.print("-");
        }
        if (depth > 0) {
            System.out.print(" ");
        }
        for (int i = 0; i < depth - 1; i++) {
            if (leftTrace[i] == '|' || rightTrace[i] == '|') {
                System.out.print("| ");
            } else {
                System.out.print("  ");
            }
        }
        if (depth > 0) {
            System.out.print(prefix + "-");
        }
        System.out.println("[" + node.value + "]");
        leftTrace[depth] = ' ';
        if (node.right != null) {
            rightTrace[depth] = '|';
            printTreeRecursive(node.right, depth + 1, '\\', leftTrace, rightTrace);
        }
    }

    public int height() {
        if (root == null) {
            return 0;
        }

        Queue<Node> queue = new LinkedList<>();
        queue.add(root);
        int height = 0;

        while (!queue.isEmpty()) {
            int levelSize = queue.size();
            height++;

            for (int i = 0; i < levelSize; i++) {
                Node currentNode = queue.poll();

                if (currentNode.left != null) {
                    queue.add(currentNode.left);
                }

                if (currentNode.right != null) {
                    queue.add(currentNode.right);
                }
            }
        }

        return height;
    }
}

