import java.util.LinkedList;
import java.util.Queue;

public class SplayTree {
    private Node root;
    
    private long comparisonCount;
    private long readCount;
    private long assignmentCount;

    public SplayTree() {
        root = null;
    }

    public void insert(int value) {
        Node addedNode = new Node(value);
        insert(addedNode);
    }

    public void insert(Node z) {
        Node x = root;
        Node y = null;

        while (x != null) {
        		comparisonCount++;
            y = x;
            comparisonCount++;
            if (x.value < z.value) {
                x = x.right;
                readCount++;
            } else {
                x = x.left;
                readCount++;
            }
        }

        x = z;
        x.parent = y;
        assignmentCount++;
        comparisonCount++;
        if (y == null) {
            root = x;
            assignmentCount++;
        } else if (y.value < x.value) {
            y.right = x;
            assignmentCount++;
            comparisonCount++;
        } else {
            y.left = x;
            assignmentCount++;
            comparisonCount++;
        }

        splay(x);
    }

    public void delete(int value) {
        Node nodeToDelete = findNode(root, value);
        comparisonCount++;
        if (nodeToDelete != null) {
            delete(nodeToDelete);
        }
    }

    public void delete(Node z) {
        comparisonCount++;
        if (z == null) {
            return;
        }
        splay(z);
		  comparisonCount++;
        if (z.left == null) {
            transplant(z, z.right);
        } else if (z.right == null) {
            comparisonCount++;
            transplant(z, z.left);
        } else {
        		comparisonCount++;
            Node y = treeMinimum(z.right);
            assignmentCount++;
            comparisonCount++;
            if (y.parent != z) {
                transplant(y, y.right);
                y.right = z.right;
                assignmentCount++;
                readCount++;
                y.right.parent = y;
                assignmentCount++;
            }
            transplant(z, y);
            y.left = z.left;
            assignmentCount++;
            readCount++;
            y.left.parent = y;
            assignmentCount++;
        }
    }

    private Node findNode(Node root, int value) {
        Node current = root;
        while (current != null && current.value != value) {
            comparisonCount+=2;
            comparisonCount++;
            if (value < current.value) {
                current = current.left;
                assignmentCount++;
                readCount++;
            } else {
                current = current.right;
            	 assignmentCount++;
            	 readCount++;
            }
        }
        comparisonCount++;
        return current;
    }

    private void transplant(Node u, Node v) {
        comparisonCount++;
        if (u.parent == null) {
            root = v;
            assignmentCount++;
        } else if (u == u.parent.left) {
            comparisonCount++;
            u.parent.left = v;
            assignmentCount++;
        } else {
            comparisonCount++;
            u.parent.right = v;
            assignmentCount++;
        }
        comparisonCount++;
        if (v != null) {
            v.parent = u.parent;
            assignmentCount++;
        		readCount++;
        }
    }

    private Node treeMinimum(Node x) {
        while (x.left != null) {
            comparisonCount++;
            x = x.left;
            assignmentCount++;
            readCount++;
        }
        comparisonCount++;
        return x;
    }

    private void leftRotate(Node x) {
        Node y = x.right;
        assignmentCount++;
        readCount++;
        comparisonCount++;
        if (y != null) {
            x.right = y.left;
            assignmentCount++;
            readCount++;
            comparisonCount++;
            if (y.left != null) y.left.parent = x;
            y.parent = x.parent;
            assignmentCount++;
            readCount++;
        }
        comparisonCount++;
        if (x.parent == null){ 
        		assignmentCount++;
        		root = y;
        }
        else if (x == x.parent.left){
         	readCount++;
         	comparisonCount++;
         	x.parent.left = y;
         	assignmentCount++;
        } 
        else{
        		comparisonCount++;
        		x.parent.right = y;
        		assignmentCount++;
        }
        comparisonCount++;
        if (y != null){
         	y.left = x;
        		assignmentCount++;
        }
        x.parent = y;
    	  assignmentCount++;
    }

    private void rightRotate(Node x) {
        Node y = x.left;
        assignmentCount++;
        readCount++;
        comparisonCount++;
        if (y != null) {
        		readCount++;
            x.left = y.right;
            assignmentCount++;
            comparisonCount++;
            if (y.right != null){
            	assignmentCount++;
            	y.right.parent = x;
            }
            y.parent = x.parent;
            assignmentCount++;
            readCount++;
        }
        comparisonCount++;
        if (x.parent == null){
        		assignmentCount++;
        		root = y;
        }
        else if (x == x.parent.left){
        		comparisonCount++;
        		x.parent.left = y;
        		assignmentCount++;
        }
        else{
        		comparisonCount++;
         	x.parent.right = y;
        		assignmentCount++;
        }
        comparisonCount++;
        if (y != null){
        		y.right = x;
        		assignmentCount++;
        }
        x.parent = y;
    	  assignmentCount++;
    }

    private void splay(Node x) {
        while (x.parent != null) {
        		comparisonCount++;
        		comparisonCount++;
            if (x.parent.parent == null) {
            	 comparisonCount++;
                if (x.parent.left == x) rightRotate(x.parent);
                else leftRotate(x.parent);
            } else if (x.parent.left == x && x.parent.parent.left == x.parent) {
                comparisonCount++;
                rightRotate(x.parent.parent);
                rightRotate(x.parent);
            } else if (x.parent.right == x && x.parent.parent.right == x.parent) {
                comparisonCount+=2;
                leftRotate(x.parent.parent);
                leftRotate(x.parent);
            } else if (x.parent.left == x && x.parent.parent.right == x.parent) {
                comparisonCount+=3;
                rightRotate(x.parent);
                leftRotate(x.parent);
            } else {
                comparisonCount+=3;
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
        comparisonCount++;
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
					 readCount++;

                if (currentNode.left != null) {
                	  comparisonCount++;
                    queue.add(currentNode.left);
                    readCount++;
                }

                if (currentNode.right != null) {
                    comparisonCount++;
                    queue.add(currentNode.right);
                	  readCount++;
                }
            }
        }

        return height;
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

