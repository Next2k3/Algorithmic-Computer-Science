
public class BinarySearchTree {
	private Node root;
	
	public BinarySearchTree() {
		root = null;
	}
	
	public void insert(int value) {
		root = insertNode(root, value);
		System.out.println(value + " added to tree");
	}
	
	private Node insertNode(Node root, int value) {
		if(root == null) {
			root = new Node(value);
			return  root;
		}
		if(value < root.value) {
			root.left = insertNode(root.left, value);
		} else if (value >= root.value) {
			root.right = insertNode(root.right, value);
		}
		return root;
	}
	
	public void delete(int value) {
		if(contains(value)){
			root = deleteNode(root, value);
			if(root != null) {
				System.out.println(value + " deleted from tree");
			}
		}else{
			System.out.println(value + " not found in tree");
		}
	}
	
	private Node deleteNode(Node root, int value) {
		if(root == null) return root;
		
		if(value < root.value){
			root.left = deleteNode(root.left, value);
		} else if(value > root.value){
			root.right = deleteNode(root.right, value);
		} else {
			if(root.left == null){
				return root.right;
			} else if(root.right == null){
				return root.left;
			}
			
			root.value = minValue(root.right);
			root.right = deleteNode(root.right, root.value);
		}
		return root;
	}
	
	public boolean contains(int value) {
      return containsNode(root, value);
	}

   private boolean containsNode(Node root, int value) {
      if (root == null) {
     		return false;
     	}
      if (value == root.value) {
         return true;
     	}
      return value < root.value ? containsNode(root.left, value) : containsNode(root.right, value);
  	}

	
	private int minValue(Node root) {
		int minValue = root.value;
		while (root.left != root && root.left != null) {
			minValue = root.left.value;
			root = root.left;
		}
		return minValue;	
	}
	
	public int height() {
		return heightNode(root);
	}
	
	private int heightNode(Node root) {
		if(root == null) return 0;
		return Math.max(heightNode(root.left), heightNode(root.right)) + 1;
	}
	
	public void printTree() {
   	int height = height();
      char[] leftTrace = new char[height];
      char[] rightTrace = new char[height];
      printTreeRecursive(root, 0, '-', leftTrace, rightTrace);
   }

   private void printTreeRecursive(Node node, int depth, char prefix, char[] leftTrace, char[] rightTrace) {
   	if(node == null) {
      	return;
      }

      if(node.left != null) {
         printTreeRecursive(node.left, depth + 1, '/', leftTrace, rightTrace);
      }

      if(prefix == '/') {
         leftTrace[depth - 1] = '|';
      }
      if(prefix == '\\') {
         rightTrace[depth - 1] = ' ';
      }
      if(depth == 0) {
         System.out.print("-");
      }
      if(depth > 0) {
         System.out.print(" ");
      }
      for(int i = 0; i < depth - 1; i++) {
         if(leftTrace[i] == '|' || rightTrace[i] == '|') {
         	System.out.print("| ");
         }else {
            System.out.print("  ");
         }
      }
      if(depth > 0) {
         System.out.print(prefix + "-");
      }
      System.out.println("[" + node.value + "]");
      leftTrace[depth] = ' ';
      if(node.right != null) {
         rightTrace[depth] = '|';
         printTreeRecursive(node.right, depth + 1, '\\', leftTrace, rightTrace);
      }
  	}
}
