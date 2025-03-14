import java.util.Random;
import java.util.Arrays;

public class RandomizedSelect {
    private static int swaps;
    private static int comparisons;
    private static int arrayLength = 0;
    private static int[] initialArray;

    RandomizedSelect() {
        this.swaps = 0;
        this.comparisons = 0;
    }

    public static int randomizedSelect(int[] array, int k) {
        arrayLength = array.length;
        initialArray = array;
        System.out.println("RANDOMIZED SELECT");
        printInitialArray();
        return randomizedSelect(array, 0, array.length - 1, k);
    }

    private static int randomizedSelect(int[] array, int low, int high, int k) {
        print(array);
        if (low == high) {
            return array[low];
        }

        int r = randomizedPartition(array, low, high);
        int rank = r - low;

        if (k == rank) {
            return array[r];
        } else if (k < rank) {
            return randomizedSelect(array, low, r - 1, k);
        } else {
            return randomizedSelect(array, r + 1, high, k - rank - 1);
        }
    }

    private static int randomizedPartition(int[] array, int low, int high) {
        Random random = new Random();
        int i = random.nextInt(high - low + 1) + low;
        swap(array, i, high);
        return partition(array, low, high);
    }

    private static int partition(int[] array, int low, int high) {
        int pivot = array[high];
        int i = low;

        for (int j = low; j < high; j++) {
            comparisons++;
            if (array[j] <= pivot) {
                swap(array, i, j);
                i++;
            }
        }
        swap(array, i, high);
        return i;
    }

    private static void print(int[] array) {
        if (array.length < 50) {
            for (int value : array) {
                if (value < 10) {
                    System.out.print(" " + value + " ");
                } else {
                    System.out.print(value + " ");
                }
            }
            System.out.println();
        }
    }

    private static void printInitialArray() {
        if (arrayLength < 50) {
            System.out.println("INITIAL ARRAY:");
            print(initialArray);
            System.out.println();
        }
    }

    public static void printStatistics() {
        System.out.println();
        if (arrayLength < 50) {
            System.out.println("SORTED ARRAY: ");
            int[] sortedArray = Arrays.copyOf(initialArray, arrayLength);
            Arrays.sort(sortedArray);
            print(sortedArray);
            System.out.println();
        }
        System.out.println("swaps: " + swaps);
        System.out.println("comparisons: " + comparisons);
    }

    private static void swap(int[] array, int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        swaps++;
    }

    public static int getSwaps() {
        return swaps;
    }

    public static int getComparisons() {
        return comparisons;
    }
}
