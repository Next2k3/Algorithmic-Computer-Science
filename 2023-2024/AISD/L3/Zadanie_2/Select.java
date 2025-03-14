import java.util.Arrays;
import java.lang.Math;

public class Select {
    private int partitionSize;
    private long swaps = 0;
    private long comparisons = 0;
    private int arrayLength = 0;
    private int[] initialArray;

    Select(int partitionSize) {
        this.partitionSize = partitionSize;
    }

    public int select(int[] array, int k) {
        arrayLength = array.length;
        initialArray = array;
        System.out.println("SELECT");
        printInitialArray();
        if (k < 0 || k >= arrayLength) {
            return -1;
        }
        
        return selectPivot(array, k);
    }

    public int selectPivot(int[] arr, int k) {
        int numPartitions = (int) Math.ceil((double) arr.length / partitionSize);
        int[][] partitions = new int[numPartitions][partitionSize];

        for (int i = 0; i < numPartitions; i++) {
            int start = i * partitionSize;
            int end = Math.min(start + partitionSize, arr.length);
            partitions[i] = Arrays.copyOfRange(arr, start, end);
            if (end - start > partitionSize) {
                for (int h = start + 1; h < end; h++) {
                    int j = h;
                    comparisons++;
                    while (j > start && arr[j - 1] > arr[j]) {
                        comparisons++;
                        swap(arr, j - 1, j);
                        j--;
                    }
                }
            }
        }

        int[] medians = new int[numPartitions];
        for (int i = 0; i < numPartitions; i++) {
            medians[i] = partitions[i][partitions[i].length / 2];
        }

        int pivot;
        if (medians.length <= partitionSize) {
            int start = 0;
            int end = medians.length;
            for (int h = start + 1; h < end; h++) {
                int j = h;
                comparisons++;
                while (j > start && arr[j - 1] > arr[j]) {
                    comparisons++;
                    swap(arr, j - 1, j);
                    j--;
                }
            }
            pivot = medians[medians.length / 2];
        } else {
            pivot = selectPivot(medians, medians.length / 2);
        }

        int p = partition(arr, pivot);

        if (k == p) {
            return pivot;
        }

        if (k < p) {
            return selectPivot(Arrays.copyOfRange(arr, 0, p), k);
        } else {
            return selectPivot(Arrays.copyOfRange(arr, p + 1, arr.length), k - p - 1);
        }
    }

    public int partition(int[] arr, int pivot) {
        int left = 0;
        int right = arr.length - 1;
        int i = 0;

        while (i <= right) {
            comparisons++;
            if (arr[i] == pivot) {
                i++;
            } else if (arr[i] < pivot) {
                swap(arr, left, i);
                left++;
                i++;
            } else {
                swap(arr, right, i);
                right--;
            }
        }
        return left;
    }

    private void print(int[] array) {
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

    private void printInitialArray() {
        if (arrayLength < 50) {
            System.out.println("INITIAL ARRAY:");
            print(initialArray);
            System.out.println();
        }
    }

    public void printStatistics() {
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
        System.out.println("partiton size: " + partitionSize);
    }


    private void swap(int[] array, int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        swaps++;
    }

    public long getSwaps() {
        return swaps;
    }

    public long getComparisons() {
        return comparisons;
    }
}
