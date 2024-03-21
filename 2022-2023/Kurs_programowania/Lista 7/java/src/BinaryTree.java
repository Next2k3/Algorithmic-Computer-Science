public class BinaryTree<T extends Comparable<T>> {
    private Node root;
    private String printedTree="";
    private class Node{
        T value;
        Node left;
        Node right;
        public Node(T value){
            this.value = value;
            left = null;
            right = null;
        }
    }
    public boolean isEmpty(){
        if(root==null)return true;
        return false;
    }
    public void insert(T value){
        root = insertNode(root, value);
    }
    public void delete(T value){
        root = deleteNode(root,value);
    }
    public boolean search(T value){
        return searchNode(root,value);
    }
    public String draw(){
        printedTree="";
        drawInorder(root);
        return printedTree;
    }
    private Node insertNode(Node root,T value){
        if(root== null){
            root = new Node(value);
            return root;
        }
        if(value.compareTo(root.value)<0){
            root.left = insertNode(root.left,value);
        }else if(value.compareTo(root.value)>0){
            root.right=insertNode(root.right,value);
        }
        return root;
    }
    private Node deleteNode(Node root,T value){
        if(root == null){
            return null;
        }
        if(value.compareTo(root.value)<0) {
            root.left = deleteNode(root.left, value);
        } else if (value.compareTo(root.value)>0) {
            root.right = deleteNode(root.right,value);
        }else{
            if(root.left==null){
                return root.right;
            }else if(root.right==null){
                return root.left;
            }

            root.value = findMin(root.right);
            root.right = deleteNode(root.right, root.value);
        }
        return root;
    }
    private T findMin(Node node){
        while (node.left != null){
            node=node.left;
        }
        return node.value;
    }
    private boolean searchNode(Node root,T value){
        if(root == null){
            return false;
        }
        if(value.compareTo(root.value)==0){
            return true;
        }else if(value.compareTo(root.value)<0){
            return searchNode(root.left,value);
        }else{
            return searchNode(root.right,value);
        }
    }
    /*

     */
    private void drawInorder(Node root){
        if(root == null) {
            return;
        }
        printedTree+="(";
        drawInorder(root.left);
        printedTree+=" "+root.value+" ";
        drawInorder(root.right);
        printedTree+=")";
    }
}
