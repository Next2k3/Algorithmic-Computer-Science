import java.util.List;

public class Main {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java RandGen <array_size>");
            System.exit(1);
        }

        int n = Integer.parseInt(args[0]);
        if (n <= 0) {
            System.err.println("Array size must be a positive integer.");
            System.exit(1);
        }

        int v = Integer.parseInt(args[1]);
        if (v <= 0) {
            System.err.println("v must be a positive integer.");
            System.exit(1);
        }

        List<Integer> array = SortedArray.generateRandomSortedKeys(n);
        int result = BinarySearch.binarySearch(array, v);
        System.out.println(array);
        if (result == 1) {
            System.out.println(v + " is in a array.");
        } else {
            System.out.println(v + " is not in a array.");
        }
        System.out.println("Comparisons: " + BinarySearch.getComparisons());
    }
}
