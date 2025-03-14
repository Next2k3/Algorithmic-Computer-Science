import java.util.Scanner;

public class QuickSort {
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

        System.out.print("Original array: ");
        printArray(data);
        System.out.println();

        int[] originalData = data.clone();

        long startTime = System.nanoTime();
        quickSort(data, 0, data.length - 1);
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
        int pivotIndex = low + (high - low) / 2;
        int pivot = arr[pivotIndex];
        int i = low;
        int j = high;
        while (true) {
            while (compareKeys(arr[i], pivot)) i++;
            while (compareKeys(pivot, arr[j])) j--;
            if (i >= j) return j;
            swapKeys(arr, i, j);
            i++;
            j--;

            printArray(arr);
        }
    }

    static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi);
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
