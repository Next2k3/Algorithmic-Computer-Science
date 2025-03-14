import java.util.Scanner;
import java.util.StringTokenizer;

public class DualPivotSelect {

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

        int[] originalData = data;

        long startTime = System.nanoTime();
        dualPivotQuickSort(data, 0, n - 1);
        long endTime = System.nanoTime();
        long time = endTime - startTime;

        System.out.println();
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
        System.out.println("Time: " + time);
    }

    static void printArray(int[] arr) {
        if (arr.length < 40) {
            for (int key : arr) {
                System.out.printf("%2d ", key);
            }
            System.out.println();
        }
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

    static void insertionSort(int[] array, int low, int high) {
        int key;
        for(int j = low + 1; j <= high; j++) {
            key = array[j];
            int i = j - 1;
            while (i >= 0 && compareKeys(key, array[i])) {
                array[i + 1] = array[i];
                i--;
            }
            array[i+1] = key;
        }
    }

    static int dualPartition(int[] array, int start, int end, int[] leftPivotIndex, int leftPivotValue, int rightPivotValue) {
        int rightPivotIndex = 0;
        boolean leftFound = false;
        boolean rightFound = false;
        for(int i = start; i <= end; i++) {
            if(!leftFound && leftPivotValue == array[i]) {
                leftPivotIndex[0] = i;
                leftFound = true;
            }
            else if(!rightFound && rightPivotValue == array[i]) {
                rightPivotIndex = i;
                rightFound = true;
            }
            if(leftFound && rightFound) {
                break;
            }
        }
        if(leftPivotIndex[0] != start) {
            swapKeys(array, leftPivotIndex[0], start);
            leftPivotIndex[0] = start;
        }
        if(rightPivotIndex != end) {
            swapKeys(array, rightPivotIndex, end);
            rightPivotIndex = end;
        }
        int lowIndex = start + 1;
        int highIndex = end - 1;
        for (int j = start+1; j <= highIndex; j++) {
            if (compareKeys(array[j], leftPivotValue)) {
                swapKeys(array, j, lowIndex);
                lowIndex++;
            }
            else if (compareKeys(rightPivotValue, array[j])) {
                while (compareKeys(rightPivotValue, array[highIndex]) && j < highIndex ) {
                    highIndex--;
                }
                swapKeys(array, j, highIndex);
                highIndex--;
                if (compareKeys(array[j], leftPivotValue)) {
                    swapKeys(array, j, lowIndex);
                    lowIndex++;
                }
            }
        }
        lowIndex--;
        highIndex++;

        swapKeys(array, start, lowIndex);
        swapKeys(array, end, highIndex);
        printArray(array);

        leftPivotIndex[0] = lowIndex;
        return highIndex;
    }

    static int partition(int[] arr, int p, int q, int pivot) {
        int pivotIndex = 0;
        for(int i = p; i <= q; i++) {
            if(pivot == arr[i]) {
                pivotIndex = i;
                break;
            }
        }
        if(pivotIndex != p)
            swapKeys(arr, pivotIndex, p);
        pivotIndex = p;
        int j = p;
        for(int i = p + 1; i <= q; i++) {
            if(compareKeys(arr[i], arr[pivotIndex])) {
                j++;
                swapKeys(arr, j, i);
            }
        }
        swapKeys(arr, j, p);
        return j;
    }

    static int select(int[] arr, int p, int q, int i) {
        if (p == q) {
            return arr[p];
        }
        int medianTabSize = (((q - p + 1) % 5 == 0) ? ((q - p + 1) / 5): (((q - p + 1) / 5) + 1));
        int[] medianTab = new int[medianTabSize];
        int index = 0;
        for(int j = p; j <= q; j += 5) {
            if(j + 4 <= q) {
                insertionSort(arr, j, j + 4);
                medianTab[index] = arr[j + 2];
                index++;
            }
            else {
                insertionSort(arr, j, q);
                medianTab[index] = arr[j + ((q - j) / 2)];
            }
        }
        int medianOfMedian = select(medianTab, 0, medianTabSize - 1, ((medianTabSize + 1) / 2));
        int r = partition(arr, p, q, medianOfMedian);
        int k = r - p + 1;
        if (k == i) return arr[r];
        else if (i < k) return select(arr, p, r - 1, i);
        else return select(arr, r + 1, q, i - k);
    }

    static void dualPivotQuickSort(int[] array, int start, int end) {
        if(start < end - 1) {
            int[] p = new int[1];
            int[] q = new int[1];
            int pValue = select(array, start, end, ((end - start + 1) / 3));
            int qValue = select(array, start, end, ((end - start + 1) / 3) * 2);

            q[0] = dualPartition(array, start, end, p, pValue, qValue);
            dualPivotQuickSort(array, start, p[0] - 1);
            dualPivotQuickSort(array, p[0] + 1, q[0] - 1);
            dualPivotQuickSort(array, q[0] + 1, end);
        }
        else if(start == end - 1) {
            if(compareKeys(array[end], array[start])) {
                swapKeys(array, start, end);
            }
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
