import java.util.Stack;

public class RedBlackBinarySearchTree {
    private Node root;
    private static final boolean RED = true;
    private static final boolean BLACK = false;

    public RedBlackBinarySearchTree() {
        root = null;
    }

    public void insert(int value) {
     	System.out.println(value + " added to tree");
        Node newNode = new Node(value);
        if (root == null) {
            root = newNode;
            root.color = BLACK;
            return;
        }

        Node current = root;
        Node parent = null;
        while (current != null) {
            parent = current;
            if (value < current.value) {
                current = current.left;
            } else if (value > current.value) {
                current = current.right;
            } else {
                return;
            }
        }

        if (value < parent.value) {
            parent.left = newNode;
        } else {
            parent.right = newNode;
        }
        newNode.parent = parent;
        fixInsert(newNode);
    }

    private void fixInsert(Node node) {
        Node parent = null;
        Node grandParent = null;

        while (node != root && node.color == RED && node.parent.color == RED) {
            parent = node.parent;
            grandParent = parent.parent;

            if (parent == grandParent.left) {
                Node uncle = grandParent.right;
                if (uncle != null && uncle.color == RED) {
                    grandParent.color = RED;
                    parent.color = BLACK;
                    uncle.color = BLACK;
                    node = grandParent;
                } else {
                    if (node == parent.right) {
                        rotateLeft(parent);
                        node = parent;
                        parent = node.parent;
                    }
                    rotateRight(grandParent);
                    boolean temp = parent.color;
                    parent.color = grandParent.color;
                    grandParent.color = temp;
                    node = parent;
                }
            } else {
                Node uncle = grandParent.left;
                if (uncle != null && uncle.color == RED) {
                    grandParent.color = RED;
                    parent.color = BLACK;
                    uncle.color = BLACK;
                    node = grandParent;
                } else {
                    if (node == parent.left) {
                        rotateRight(parent);
                        node = parent;
                        parent = node.parent;
                    }
                    rotateLeft(grandParent);
                    boolean temp = parent.color;
                    parent.color = grandParent.color;
                    grandParent.color = temp;
                    node = parent;
                }
            }
        }
        root.color = BLACK;
    }

    private void rotateLeft(Node node) {
        Node temp = node.right;
        node.right = temp.left;
        if (temp.left != null) {
            temp.left.parent = node;
        }
        temp.parent = node.parent;
        if (node.parent == null) {
            root = temp;
        } else if (node == node.parent.left) {
            node.parent.left = temp;
        } else {
            node.parent.right = temp;
        }
        temp.left = node;
        node.parent = temp;
    }

    private void rotateRight(Node node) {
        Node temp = node.left;
        node.left = temp.right;
        if (temp.right != null) {
            temp.right.parent = node;
        }
        temp.parent = node.parent;
        if (node.parent == null) {
            root = temp;
        } else if (node == node.parent.right) {
            node.parent.right = temp;
        } else {
            node.parent.left = temp;
        }
        temp.right = node;
        node.parent = temp;
    }

    public void delete(int value) {
        if (contains(value)) {
            deleteNode(root, value);
            System.out.println(value + " deleted from tree");
        }else {
            System.out.println(value + " not found in tree");
        }
    }

    private void deleteNode(Node node, int value) {
        Node toDelete = findNode(node, value);
        if (toDelete == null) return;

        Node y = toDelete;
        Node x;
        boolean yOriginalColor = y.color;

        if (toDelete.left == null) {
            x = toDelete.right;
            transplant(toDelete, toDelete.right);
        } else if (toDelete.right == null) {
            x = toDelete.left;
            transplant(toDelete, toDelete.left);
        } else {
            y = minimum(toDelete.right);
            yOriginalColor = y.color;
            x = y.right;
            if (y.parent == toDelete) {
                if (x != null) {
                    x.parent = y;
                }
            } else {
                transplant(y, y.right);
                y.right = toDelete.right;
                if (y.right != null) {
                    y.right.parent = y;
                }
            }
            transplant(toDelete, y);
            y.left = toDelete.left;
            if (y.left != null) {
                y.left.parent = y;
            }
            y.color = toDelete.color;
        }

        if (yOriginalColor == BLACK) {
            fixDelete(x);
        }
    }

   private void fixDelete(Node node) {
		 while (node != null && node != root && (node.parent == null || node.color == BLACK)) {
		     if (node.parent != null && node == node.parent.left) {
		         Node sibling = node.parent.right;
		         if (sibling != null && sibling.color == RED) {
		             sibling.color = BLACK;
		             if (node.parent != null)
		                 node.parent.color = RED;
		             rotateLeft(node.parent);
		             sibling = node.parent.right;
		         }
		         if ((sibling == null || (sibling.left == null || sibling.left.color == BLACK)) &&
		             (sibling == null || (sibling.right == null || sibling.right.color == BLACK))) {
		             if (sibling != null)
		                 sibling.color = RED;
		             if (node.parent != null)
		                 node = node.parent;
		         } else {
		             if (sibling == null || (sibling.right == null || sibling.right.color == BLACK)) {
		                 if (sibling != null && sibling.left != null)
		                     sibling.left.color = BLACK;
		                 if (sibling != null)
		                     sibling.color = RED;
		                 rotateRight(sibling);
		                 sibling = node.parent.right;
		             }
		             if (sibling != null)
		                 sibling.color = node.parent.color;
		             if (node.parent != null)
		                 node.parent.color = BLACK;
		             if (sibling != null && sibling.right != null)
		                 sibling.right.color = BLACK;
		             rotateLeft(node.parent);
		             node = root;
		         }
		     } else {
		         Node sibling = node.parent.left;
		         if (sibling != null && sibling.color == RED) {
		             sibling.color = BLACK;
		             if (node.parent != null)
		                 node.parent.color = RED;
		             rotateRight(node.parent);
		             sibling = node.parent.left;
		         }
		         if ((sibling == null || (sibling.left == null || sibling.left.color == BLACK)) &&
		             (sibling == null || (sibling.right == null || sibling.right.color == BLACK))) {
		             if (sibling != null)
		                 sibling.color = RED;
		             if (node.parent != null)
		                 node = node.parent;
		         } else {
		             if (sibling == null || (sibling.left == null || sibling.left.color == BLACK)) {
		                 if (sibling != null && sibling.right != null)
		                     sibling.right.color = BLACK;
		                 if (sibling != null)
		                     sibling.color = RED;
		                 rotateLeft(sibling);
		                 sibling = node.parent.left;
		             }
		             if (sibling != null)
		                 sibling.color = node.parent.color;
		             if (node.parent != null)
		                 node.parent.color = BLACK;
		             if (sibling != null && sibling.left != null)
		                 sibling.left.color = BLACK;
		             rotateRight(node.parent);
		             node = root;
		         }
		     }
		 }
		 if (node != null) {
		     node.color = BLACK;
		 }
	}


    private Node findNode(Node root, int value) {
        while (root != null) {
            if (value == root.value) {
                return root;
            } else if (value < root.value) {
                root = root.left;
            } else {
                root = root.right;
            }
        }
        return null;
    }

    private void transplant(Node target, Node with) {
        if (target.parent == null) {
            root = with;
        } else if (target == target.parent.left) {
            target.parent.left = with;
        } else {
            target.parent.right = with;
        }
        if (with != null) {
            with.parent = target.parent;
        }
    }

    private Node minimum(Node node) {
        while (node.left != null) {
            node = node.left;
        }
        return node;
    }

    public boolean contains(int value) {
        return containsNode(root, value);
    }
    
    private boolean containsNode(Node root, int value) {
        Node current = root;
        while (current != null) {
            if (value == current.value) {
                return true;
            } else if (value < current.value) {
                current = current.left;
            } else {
                current = current.right;
            }
        }
        return false;
    }

    public int height() {
        return heightNode(root);
    }

    private int heightNode(Node root) {
        if (root == null) {
            return 0;
        }

        Stack<Node> nodeStack = new Stack<>();
        Stack<Integer> heightStack = new Stack<>();
        nodeStack.push(root);
        heightStack.push(1);

        int maxHeight = 0;
        while (!nodeStack.isEmpty()) {
            Node currentNode = nodeStack.pop();
            int currentHeight = heightStack.pop();

            maxHeight = Math.max(maxHeight, currentHeight);
            if (currentNode.left != null) {
                nodeStack.push(currentNode.left);
                heightStack.push(currentHeight + 1);
            }
            if (currentNode.right != null) {
                nodeStack.push(currentNode.right);
                heightStack.push(currentHeight + 1);
            }
        }

        return maxHeight;
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
        if (node.color == RED) {
            System.out.println("\033[31m[" + node.value + "]\033[0m");
        } else {
            System.out.println("[" + node.value + "]");
        }
        leftTrace[depth] = ' ';
        if (node.right != null) {
            rightTrace[depth] = '|';
            printTreeRecursive(node.right, depth + 1, '\\', leftTrace, rightTrace);
        }
    }
}
