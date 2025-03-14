import java.util.Arrays;
import java.util.Scanner;

public class QuickSortSelect {
    static int comparisonCount = 0;
    static int swapCount = 0;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter integers separated by spaces:");
        String input = scanner.nextLine();
        String[] tokens = input.split("\\s+");
        int[] data = new int[tokens.length];
        int n = data.length;
        for (int i = 0; i < tokens.length; i++) {
            data[i] = Integer.parseInt(tokens[i]);
        }

        System.out.print("Original array: ");
        printArray(data);
        System.out.println();

        int[] originalData = Arrays.copyOf(data, n);

        long startTime = System.nanoTime();
        quickSort(data, 0, n - 1);
        long endTime = System.nanoTime();
        long time = endTime - startTime;

        System.out.println();

        System.out.print("Original array: ");
        printArray(originalData);
        System.out.print("Sorted array:   ");
        printArray(data);
        System.out.println();

        if (isSorted(data)) {
            System.out.println("The array is sorted correctly.");
        } else {
            System.out.println("Error: The array is not sorted correctly!");
        }

        System.out.println("Swaps: " + swapCount);
        System.out.println("Comparisons: " + comparisonCount);
        System.out.println("Time: " + time + " nanoseconds");
    }

    static void printArray(int[] arr) {
        for (int key : arr) {
            System.out.print(key + " ");
        }
        System.out.println();
    }

    static boolean compareKeys(int a, int b) {
        comparisonCount++;
        return a < b;
    }

    static void swapKeys(int[] arr, int index1, int index2) {
        int temp = arr[index1];
        arr[index1] = arr[index2];
        arr[index2] = temp;
        swapCount++;
    }

    static int partition(int[] arr, int low, int high, int pivotIndex) {
        int pivot = arr[pivotIndex];
        swapKeys(arr, pivotIndex, high); // Move pivot to end
        int i = low;
        for (int j = low; j < high; ++j) {
            if (compareKeys(arr[j], pivot)) {
                swapKeys(arr, i, j);
                i++;
            }
        }
        swapKeys(arr, i, high); // Move pivot to its final place
        printArray(arr);
        return i;
    }

    static int insertionSort(int[] array, int low, int high) {
        for (int i = low + 1; i <= high; i++) {
            int j = i;
            comparisonCount++;
            while (j > low && array[j - 1] > array[j]) {
                comparisonCount++;
                swapKeys(array, j - 1, j);
                j--;
            }
        }
        return low + (high - low) / 2;
    }

    static int medianOfMedians(int[] arr, int low, int high) {
        final int groupSize = 5;
        int n = high - low + 1;
        if (n <= groupSize) {
            return insertionSort(arr, low, high);
        }
        for (int i = 0; i < n / groupSize; ++i) {
            int left = low + i * groupSize;
            int right = left + groupSize - 1;
            if (right > high) right = high;
            int medianIndex = medianOfMedians(arr, left, right);
            swapKeys(arr, low + i, medianIndex);
        }
        return medianOfMedians(arr, low, low + n / groupSize - 1);
    }

    static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int pivotIndex = medianOfMedians(arr, low, high);
            int pi = partition(arr, low, high, pivotIndex);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    static boolean isSorted(int[] arr) {
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] < arr[i - 1]) {
                return false;
            }
        }
        return true;
    }
}
