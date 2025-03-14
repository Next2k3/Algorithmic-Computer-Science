import java.util.Arrays;
import java.util.Scanner;
import java.util.Vector;

public class BadQuickSort {
    static int comparisonCount = 0;
    static int swapCount = 0;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter integers separated by spaces:");
        String input = scanner.nextLine();
        String[] tokens = input.split("\\s+");
        int[] data = new int[tokens.length];
        for (int i = 0; i < tokens.length; i++) {
            data[i] = Integer.parseInt(tokens[i]);
        }

        int n = data.length;

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

    static int partition(int[] arr, int low, int high) {
        int pivotIndex = high;
        int pivot = arr[pivotIndex];
        int i = low - 1;
        for (int j = low; j <= high; j++) {
            if (compareKeys(arr[j], pivot)) {
                i++;
                swapKeys(arr, i, j);
            }
        }
        swapKeys(arr, i + 1, high);
        printArray(arr);
        return i + 1;
    }

    static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
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
