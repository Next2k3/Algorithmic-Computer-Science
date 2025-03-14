import java.io.FileWriter;
import java.io.IOException;
import java.util.List;
import java.util.Random;

public class SecondTest {
    public static void main(String[] args) {
        try {
            FileWriter writer = new FileWriter("second.txt");
            for (int n = 1000; n <= 100000; n = n + 1000) {
                int sum = 0;
                for (int k = 0; k < 10; k ++) {
                    List<Integer> array = SortedArray.generateRandomSortedKeys(n);
                    int v;
                    long timeSum, startTime, endTime;

                    Random rand = new Random();
                    int index = rand.nextInt(n - 1);
                    v = array.get(index);

                    startTime = System.nanoTime();
                    BinarySearch.binarySearch(array, v);
                    endTime = System.nanoTime();
                    timeSum = endTime - startTime;
                    //System.out.println(String.valueOf(endTime) + " " + String.valueOf(startTime) + " " + String.valueOf(timeSum));
                    int comparisons = BinarySearch.getComparisons();
                    sum += comparisons;
                    BinarySearch.setComparisons(0);
                    writer.write(String.valueOf(n) + " " + String.valueOf(k) + " " + String.valueOf(comparisons) + " " + String.valueOf(timeSum) + "\n");
                }
                System.out.println("Average of comparisons for " + n + ": " + sum/10);
            }
            writer.close();
        } catch (IOException e) {
            System.out.println("Wystąpił błąd podczas zapisu do pliku.");
            e.printStackTrace();
        }
    }
}
