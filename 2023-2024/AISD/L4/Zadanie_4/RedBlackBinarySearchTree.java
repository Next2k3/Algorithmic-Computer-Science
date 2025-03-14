import java.util.Stack;

public class RedBlackBinarySearchTree {
    private Node root;
    
    private static final boolean RED = true;
    private static final boolean BLACK = false;
    
    private long comparisonCount;
    private long readCount;
    private long assignmentCount;

    public RedBlackBinarySearchTree() {
        root = null;
        comparisonCount = 0;
        readCount = 0;
        assignmentCount = 0;
    }

    public void insert(int value) {
        Node newNode = new Node(value);
        comparisonCount++;
        if (root == null) {
        		assignmentCount++;
            root = newNode;
            assignmentCount++;
            root.color = BLACK;
            return;
        }
			
        Node current = root;
        Node parent = null;
        while (current != null) {
        		comparisonCount++;
        		assignmentCount++;
            parent = current;
            if (value < current.value) {
            	 comparisonCount++;
            	 readCount++;
            	 assignmentCount++;
                current = current.left;
            } else if (value > current.value) {
            	 comparisonCount+=2;
            	 readCount++;
            	 assignmentCount++;
                current = current.right;
            } else {
            	 comparisonCount+=2;
                return;
            }
        }
		  comparisonCount++;
        if (value < parent.value) {
        		assignmentCount++;
            parent.left = newNode;
        } else {
        		assignmentCount++;
            parent.right = newNode;
        }
        assignmentCount++;
        newNode.parent = parent;
        fixInsert(newNode);
    }

    private void fixInsert(Node node) {
        Node parent = null;
        Node grandParent = null;

        while (node != root && node.color == RED && node.parent.color == RED) {
            comparisonCount+=3;
            readCount++;
            assignmentCount++;
            parent = node.parent;
            readCount++;
            assignmentCount++;
            grandParent = parent.parent;
				comparisonCount++;
            if (parent == grandParent.left) {
            	 readCount++;
            	 assignmentCount++;
                Node uncle = grandParent.right;
                comparisonCount++;
                if (uncle != null && uncle.color == RED) {
                    assignmentCount+=3;
                    grandParent.color = RED;
                    parent.color = BLACK;
                    uncle.color = BLACK;
                    readCount++;
                    assignmentCount++;
                    node = grandParent;
                } else {
                	  comparisonCount++;
                    if (node == parent.right) {
                        rotateLeft(parent);
                        readCount++;
                        assignmentCount++;
                        node = parent;
                        readCount++;
                        assignmentCount++;
                        parent = node.parent;
                    }
                    rotateRight(grandParent);
                    assignmentCount++;
                    boolean temp = parent.color;
                    readCount++;
                    assignmentCount++;
                    parent.color = grandParent.color;
                    assignmentCount++;
                    grandParent.color = temp;
                    readCount++;
                    assignmentCount++;
                    node = parent;
                }
            } else {
                assignmentCount++;
                Node uncle = grandParent.left;
                comparisonCount+=2;
                if (uncle != null && uncle.color == RED) {
                    assignmentCount+=3;
                    grandParent.color = RED;
                    parent.color = BLACK;
                    uncle.color = BLACK;
                    readCount++;
                    assignmentCount++;
                    node = grandParent;
                } else {
                	  comparisonCount++;
                    if (node == parent.left) {
                        rotateRight(parent);
                        readCount++;
                        assignmentCount++;
                        node = parent;
                        readCount++;
                        assignmentCount++;
                        parent = node.parent;
                    }
                    rotateLeft(grandParent);
                    readCount++;
                    assignmentCount++;
                    boolean temp = parent.color;
                    readCount++;
                    assignmentCount++;
                    parent.color = grandParent.color;
                    readCount++;
                    assignmentCount++;
                    grandParent.color = temp;
                    readCount++;
                    assignmentCount++;
                    node = parent;
                }
            }
        }
        assignmentCount++;
        root.color = BLACK;
    }

    private void rotateLeft(Node node) {
        readCount++;
        assignmentCount++;
        Node temp = node.right;
        readCount++;
        assignmentCount++;
        node.right = temp.left;
        comparisonCount++;
        if (temp.left != null) {
            readCount++;
            assignmentCount++;
            temp.left.parent = node;
        }
        readCount++;
        assignmentCount++;
        temp.parent = node.parent;
        if (node.parent == null) {
        		comparisonCount++;
        		assignmentCount++;
            root = temp;
        } else if (node == node.parent.left) {
        		readCount++;
        		comparisonCount+=2;
        		assignmentCount++;
            node.parent.left = temp;
        } else {
        		readCount++;
        		comparisonCount+=2;
        		assignmentCount++;
            node.parent.right = temp;
        }
        assignmentCount+=2;
        temp.left = node;
        node.parent = temp;
    }

    private void rotateRight(Node node) {
        readCount++;
        assignmentCount++;
        Node temp = node.left;
        readCount++;
        assignmentCount++;
        node.left = temp.right;
        comparisonCount++;
        readCount++;
        if (temp.right != null) {
        		assignmentCount++;
            temp.right.parent = node;
        }
        readCount++;
        assignmentCount++;
        temp.parent = node.parent;
        if (node.parent == null) {
        		comparisonCount++;
            root = temp;
        } else if (node == node.parent.right) {
        		readCount++;
        		comparisonCount+=2;
        		assignmentCount++;
            node.parent.right = temp;
        } else {
        		readCount++;
        		comparisonCount+=2;
        		assignmentCount++;
            node.parent.left = temp;
        }
        assignmentCount+=2;
        temp.right = node;
        node.parent = temp;
    }

    public void delete(int value) {
        if (contains(value)) {
            deleteNode(root, value);
        }
    }

    private void deleteNode(Node node, int value) {
        Node toDelete = findNode(node, value);
        comparisonCount++;
        if (toDelete == null) return;

        Node y = toDelete;
        assignmentCount++;
        Node x;
        assignmentCount++;
        boolean yOriginalColor = y.color;

        if (toDelete.left == null) {
            comparisonCount++;
            readCount++;
            assignmentCount++;
            x = toDelete.right;
            transplant(toDelete, toDelete.right);
        } else if (toDelete.right == null) {
            comparisonCount+=2;
            readCount++;
            assignmentCount++;
            x = toDelete.left;
            transplant(toDelete, toDelete.left);
        } else {
        		comparisonCount+=2;
            y = minimum(toDelete.right);
            yOriginalColor = y.color;
            readCount++;
            assignmentCount++;
            x = y.right;
            comparisonCount++;
            if (y.parent == toDelete) {
            	 comparisonCount++;
                if (x != null) {
                    assignmentCount++;
                    x.parent = y;
                }
            } else {
                transplant(y, y.right);
                readCount++;
                y.right = toDelete.right;
                comparisonCount++;
                if (y.right != null) {
                    readCount++;
                    y.right.parent = y;
                }
            }
            transplant(toDelete, y);
            readCount++;
            assignmentCount++;
            y.left = toDelete.left;
            comparisonCount++;
            if (y.left != null) {
                y.left.parent = y;
            }
            readCount++;
            y.color = toDelete.color;
        }
		  comparisonCount++;
        if (yOriginalColor == BLACK) {
            fixDelete(x);
        }
    }

   private void fixDelete(Node node) {
		 while (node != null && node != root && (node.parent == null || node.color == BLACK)) {
		     comparisonCount+=4;
		     comparisonCount+=2;
		     readCount+=2;
		     if (node.parent != null && node == node.parent.left) {
		         readCount++;
		         assignmentCount++;
		         Node sibling = node.parent.right;
		         comparisonCount+=2;
		         readCount++;
		         if (sibling != null && sibling.color == RED) {
		             readCount++;
		             assignmentCount++;
		             sibling.color = BLACK;
		             comparisonCount++;
		             readCount++;
		             if (node.parent != null){
		             	  assignmentCount++;
		                 node.parent.color = RED;
		             }
		             rotateLeft(node.parent);
		             readCount++;
		             assignmentCount++;
		             sibling = node.parent.right;
		         }
		         comparisonCount+=6;
		         readCount+=2;
		         if ((sibling == null || (sibling.left == null || sibling.left.color == BLACK)) &&
		             (sibling == null || (sibling.right == null || sibling.right.color == BLACK))) {
		             comparisonCount++;
		             if (sibling != null){
		                 assignmentCount++;
		                 sibling.color = RED;
						 }
		             comparisonCount++;
		             if (node.parent != null){
		                 readCount++;
		                 node = node.parent;
		             	  assignmentCount++;
		             }
		         } else {
		             comparisonCount+=3;
		             if (sibling == null || (sibling.right == null || sibling.right.color == BLACK)) {
		                 comparisonCount+=2;
		                 if (sibling != null && sibling.left != null){
		                     sibling.left.color = BLACK;
		                 		assignmentCount++;
		                 }
		                 comparisonCount++;
		                 if (sibling != null){
		                     sibling.color = RED;
		                     assignmentCount++;
		                 }
		                 rotateRight(sibling);
		                 readCount++;
		                 sibling = node.parent.right;
		             	  assignmentCount++;
		             }
		             comparisonCount++;
		             if (sibling != null){
		                 readCount++;
		                 sibling.color = node.parent.color;
		             	  assignmentCount++;
		             }
		             comparisonCount++;
		             if (node.parent != null){
		                 node.parent.color = BLACK;
		                 assignmentCount++;
		             }
		             comparisonCount+=2;
		             if (sibling != null && sibling.right != null){
		                 sibling.right.color = BLACK;
		             	  assignmentCount++;
		             }
		             rotateLeft(node.parent);
		             node = root;
		             assignmentCount++;
		         }
		     } else {
		         readCount++;
		         Node sibling = node.parent.left;
		         assignmentCount++;
		         comparisonCount+=2;
		         if (sibling != null && sibling.color == RED) {
		             sibling.color = BLACK;
		             assignmentCount++;
		             comparisonCount++;
		             if (node.parent != null){
		                 node.parent.color = RED;
		                 assignmentCount++;
		             }
		             rotateRight(node.parent);
		             readCount++;
		             sibling = node.parent.left;
		         	 assignmentCount++;
		         }
		         comparisonCount+=6;
		         if ((sibling == null || (sibling.left == null || sibling.left.color == BLACK)) &&
		             (sibling == null || (sibling.right == null || sibling.right.color == BLACK))) {
		             comparisonCount++;
		             if (sibling != null){
		                 sibling.color = RED;
		             	  assignmentCount++;
		             }
		             comparisonCount++;
		             if (node.parent != null){
		                 readCount++;
		                 node = node.parent;
		                 assignmentCount++;
		             }
		         } else {
		             comparisonCount+=3;
		             if (sibling == null || (sibling.left == null || sibling.left.color == BLACK)) {
		                 comparisonCount+=2;
		                 if (sibling != null && sibling.right != null){
		                     sibling.right.color = BLACK;
		                     assignmentCount++;
		                 }
		                 comparisonCount++;
		                 if (sibling != null){
		                     sibling.color = RED;
		                     assignmentCount++;
		                 }
		                 rotateLeft(sibling);
		                 readCount++;
		                 sibling = node.parent.left;
		             	  assignmentCount++;
		             }
		             comparisonCount++;
		             if (sibling != null){
		                 readCount++;
		                 sibling.color = node.parent.color;
		             	  assignmentCount++;
		             }
		             comparisonCount++;
		             if (node.parent != null){
		                 node.parent.color = BLACK;
		                 assignmentCount++;
		             }
		             comparisonCount+=2;
		             if (sibling != null && sibling.left != null){
		                 sibling.left.color = BLACK;
		              	  assignmentCount++;   
		             }
		             rotateRight(node.parent);
		             node = root;
		             assignmentCount++;
		         }
		     }
		 }
		 comparisonCount++;
		 if (node != null) {
		     node.color = BLACK;
		     assignmentCount++;
		 }
	}


    private Node findNode(Node root, int value) {
        while (root != null) {
        		comparisonCount++;
        		readCount++;
            if (value == root.value) {
                comparisonCount++;
                return root;
            } else if (value < root.value) {
            	 readCount++;
                comparisonCount+=2;
                readCount++;
                root = root.left;
                assignmentCount++;
            } else {
            	 readCount++;
            	 comparisonCount+=2;
                readCount++;
                root = root.right;
                assignmentCount++;
            }
        }
        return null;
    }

    private void transplant(Node target, Node with) {
        readCount++;
        if (target.parent == null) {
            comparisonCount++;
            readCount++;
            root = with;
            assignmentCount++;
        } else if (target == target.parent.left) {
            readCount++;
            comparisonCount+=2;
            readCount++;
            target.parent.left = with;
        		assignmentCount++;
        } else {
        		readCount++;
        		comparisonCount+=2;
            readCount++;
            target.parent.right = with;
        		assignmentCount++;
        }
        comparisonCount++;
        if (with != null) {
            readCount++;
            with.parent = target.parent;
        		assignmentCount++;
        }
    }

    private Node minimum(Node node) {
        while (node.left != null) {
            comparisonCount++;
            node = node.left;
        		assignmentCount++;
        }
        return node;
    }

    public boolean contains(int value) {
        return containsNode(root, value);
    }
    
    private boolean containsNode(Node root, int value) {
        Node current = root;
        assignmentCount++;
        while (current != null) {
        		comparisonCount++;
            readCount++;
            if (value == current.value) {
            	 comparisonCount++;
                return true;
            } else if (value < current.value) {
                readCount++;
                comparisonCount+=2;
                readCount++;
                current = current.left;
            	 assignmentCount++;
            } else {
            	 readCount++;
            	 comparisonCount+=2;
                readCount++;
                current = current.right;
            	 assignmentCount++;
            }
        }
        return false;
    }

    public int height() {
        return heightNode(root);
    }

    private int heightNode(Node root) {
        comparisonCount++;
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
				assignmentCount++;
				
            maxHeight = Math.max(maxHeight, currentHeight);
            comparisonCount++;
            if (currentNode.left != null) {
            	 readCount++;
                nodeStack.push(currentNode.left);
                heightStack.push(currentHeight + 1);
            }
            comparisonCount++;
            if (currentNode.right != null) {
                readCount++;
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
 	 public void resetCounters() {
        comparisonCount = 0;
        readCount = 0;
        assignmentCount = 0;
    }

    public long getComparisons() {
        return comparisonCount;
    }

    public long getReads() {
        return readCount;
    }

    public long getAssignments() {
        return assignmentCount;
    }
}
