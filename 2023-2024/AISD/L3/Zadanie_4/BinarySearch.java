import java.util.List;

public class BinarySearch {

    private static int comparisons = 0;

    public static int binarySearch (List<Integer> array, int v) {
        return binarySearch(array, v, 0, array.size() - 1);
    }

    private static int binarySearch(List<Integer> array, int v, int low, int high) {
        if (low > high) {
            return 0;
        }
        int mid = (low + high) / 2;

        if (array.get(mid) == v) {
            comparisons++;
            return 1;
        } else if (array.get(mid) < v) {
            comparisons++;
            return binarySearch(array, v, mid + 1, high);
        } else {
            comparisons++;
            return binarySearch(array, v, low, mid - 1);
        }
    }

    public static int getComparisons() {
        return comparisons;
    }

    public static void setComparisons(int value) {
        comparisons = value;
    }
}
