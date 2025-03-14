import java.util.List;

public class Main {
    public static int size = 50;
    public static List<Integer> keysToAdd;
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java Main <data_type>");
            System.exit(1);
        }

        RedBlackBinarySearchTree bst = new RedBlackBinarySearchTree();

        String dataType = args[0];

        if (dataType.equals("asc")) {
            keysToAdd = Generator.ascendingKeys(size);
        }
        else if (dataType.equals("rand")) {
            keysToAdd = Generator.randomKeys(size);
        }
        else {
            System.err.println("data type must be either asc or rand");
            System.exit(1);
        }

        List<Integer> keysToDelete = Generator.randomKeys(size);

        for (Integer key : keysToAdd) {
            bst.insert(key);
            bst.printTree();
        }
        for (Integer key : keysToDelete) {
            bst.delete(key);
            bst.printTree();
        }
    }
}
