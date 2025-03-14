import java.util.Stack;
public class BinarySearchTree {
    private Node root;

    private long comparisonCount;
    private long readCount;
    private long assignmentCount;

    public BinarySearchTree() {
        root = null;
        comparisonCount = 0;
        readCount = 0;
        assignmentCount = 0;
    }

    public void insert(int value) {
		 Node newNode = new Node(value);
		 comparisonCount++;
		 assignmentCount++;
		 if (root == null) {
		     root = newNode;
		     assignmentCount++;
		     return;
		 }

		 Node current = root;
		 Node parent = null;
		 while (current != null) {
		 	  comparisonCount++;
		 	  readCount++;
		     parent = current;
		     if (value < current.value) {
		     		comparisonCount+=2;
		         current = current.left;
		         readCount++;
		     } else if (value > current.value) {
		     		comparisonCount+=2;
		         current = current.right;
		         readCount++;
		     } else {
		     		comparisonCount+=2;
		     		readCount++;;
		         return;
		     }
		 }
		 comparisonCount++;
		 readCount++;
		 if (value < parent.value) {
		     parent.left = newNode;
		 } else {
		     parent.right = newNode;
		 }
		 assignmentCount++;
	}


    public void delete(int value) {
    	  comparisonCount++;
        if (contains(value)) {
            root = deleteNode(root, value);
        }
    }

    private Node deleteNode(Node root, int value) {
        Node parent = null;
        Node current = root;
        
        while (current != null && current.value != value) {
            comparisonCount++;
            parent = current;
            comparisonCount++;
            readCount++;
            assignmentCount++;
            if (value < current.value) {
                current = current.left;
            } else {
                current = current.right;
            }
        }
			comparisonCount++;
        if (current == null) {
            return root;
        }

        // Case 1: Node to be deleted has no children
        readCount+=2;
        if (current.left == null && current.right == null) {
            comparisonCount+=2;
            if (current != root) {
            	comparisonCount++;
            	readCount+=2;
                if (parent.left == current) {
                    parent.left = null;
                } else {
                    parent.right = null;
                }
                assignmentCount++;
            } else {
                root = null;
            	 assignmentCount++;
            }
        }
        // Case 2: Node to be deleted has two children
      	else if (current.left != null && current.right != null) {
    			readCount+=2;
    			comparisonCount+=2;
    			Node successorParent = current;
    			readCount++;
    			Node successor = current.right;
    			readCount++;
    			while (successor.left != null) {
    				comparisonCount++;
        			successorParent = successor;
        			readCount++;
        			successor = successor.left;
        			assignmentCount++;
    			}
    			readCount++;
    			current.value = successor.value;
    			comparisonCount++;
    			readCount++;
    			if (successor == successorParent.left) {
        			successorParent.left = successor.right;
    			} else {
        			successorParent.right = successor.right;
    			}
    			assignmentCount++;
			}
        // Case 3: Node to be deleted has one child
        else {
            comparisonCount++;
            readCount++;
            Node child = (current.left != null) ? current.left : current.right;
				comparisonCount++;
            if (current != root) {
            	 comparisonCount++;
                readCount+=2;
                if (current == parent.left) {
                    parent.left = child;
                } else {
                    parent.right = child;
                }
                assignmentCount++;
            } else {
                root = child;
            	 assignmentCount++;
            }
        }

        return root;
    }

    private Node findMin(Node root) {
        while (root.left != null) {
            readCount++;
            comparisonCount++;
            readCount++;
            root = root.left;
        		assignmentCount++;
        }
        return root;
    }

    public boolean contains(int value) {
        return containsNode(root, value);
    }

    private boolean containsNode(Node root, int value) {
    Node current = root;
    assignmentCount++;
    while (current != null) {  	
        comparisonCount+=2;
        readCount++;
        if (value == current.value) {
            readCount++;
            return true;
        } else if (value < current.value) {
           	readCount++;
            current = current.left;
        		assignmentCount++;
        } else {
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

        maxHeight = Math.max(maxHeight, currentHeight);
		  comparisonCount++;
        readCount++;
        if (currentNode.left != null) {
            readCount++;
            nodeStack.push(currentNode.left);
            heightStack.push(currentHeight + 1);
        }
		  comparisonCount++;
        readCount++;
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
        comparisonCount++;
        if (node == null) {
            return;
        }
        comparisonCount++;
        if (node.left != null) {
            printTreeRecursive(node.left, depth + 1, '/', leftTrace, rightTrace);
        }
        comparisonCount++;
        if (prefix == '/') {
            leftTrace[depth - 1] = '|';
        }
        comparisonCount++;
        if (prefix == '\\') {
            rightTrace[depth - 1] = ' ';
        }
        comparisonCount++;
        if (depth == 0) {
            System.out.print("-");
        }
        comparisonCount++;
        if (depth > 0) {
            System.out.print(" ");
        }
        for (int i = 0; i < depth - 1; i++) {
            comparisonCount++;
            if (leftTrace[i] == '|' || rightTrace[i] == '|') {
                System.out.print("| ");
            } else {
                System.out.print("  ");
            }
        }
        comparisonCount++;
        if (depth > 0) {
            System.out.print(prefix + "-");
        }
        System.out.println("[" + node.value + "]");
        leftTrace[depth] = ' ';
        comparisonCount++;
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

