import java.io.FileWriter;
import java.io.IOException;
import java.util.List;
import java.util.Random;

public class Test {

    public static void main(String[] args) {
        String[] filenames = {"beginning.txt", "middle.txt", "end.txt", "notin.txt"};

        for (String filename : filenames) {
            try {
                FileWriter writer = new FileWriter(filename);
                for (int n = 1000; n <= 100000; n = n + 1000) {
                    List<Integer> array = SortedArray.generateRandomSortedKeys(n);
                    int x, v;
                    long timeSum, startTime, endTime;

                    if (filename.equals("beginning.txt")) {
                        x = n / 3;
                    } else if (filename.equals("middle.txt")) {
                        x = 2 * n / 3;
                    } else {
                        x = n;
                    }
                    if (filename.equals("notin.txt")) {
                        v = randomNumberNotInArray(array, n);
                    } else {
                        v = array.get(randomNumber(x, n));
                    }

                    startTime = System.nanoTime();
                    int result = BinarySearch.binarySearch(array, v);
                    endTime = System.nanoTime();
                    timeSum = (endTime - startTime) / 100;
                    //System.out.println(String.valueOf(endTime) + " " + String.valueOf(startTime) + " " + String.valueOf(timeSum));
                    int comparisons = BinarySearch.getComparisons();
                    BinarySearch.setComparisons(0);
                    writer.write(String.valueOf(n) + " " + String.valueOf(comparisons) + " " + String.valueOf(timeSum) + "\n");
                }
                writer.close();
            } catch (IOException e) {
                System.out.println("Wystąpił błąd podczas zapisu do pliku.");
                e.printStackTrace();
            }
        }
    }

    private static int randomNumber(int max, int n) {
        Random rand = new Random();
        int min = max - n / 3;
        int index = rand.nextInt(max - min + 1) + min;
        if (index >= n) { return n - 1; }
        return index;
    }

    private static int randomNumberNotInArray(List<Integer> array, int n) {
        Random rand = new Random();
        int randomNumber;

        do {
            randomNumber = rand.nextInt(2 * n);
        } while (array.contains(randomNumber));

        return randomNumber;
    }
}
