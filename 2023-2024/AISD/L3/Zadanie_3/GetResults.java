import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class GetResults {

    public static void main(String[] args) {
        String inputFile = "randomData.txt";
        String outputFileSp3 = "Sresults_p_3.txt";
        String outputFileSp5 = "Sresults_p_5.txt";
        String outputFileSp7 = "Sresults_p_7.txt";
        String outputFileSp9 = "Sresults_p_9.txt";

        double k = 0.5;

        try (BufferedReader inFile = new BufferedReader(new FileReader(inputFile));
             FileWriter outFileSp3 = new FileWriter(outputFileSp3);
             FileWriter outFileSp5 = new FileWriter(outputFileSp5);
             FileWriter outFileSp7 = new FileWriter(outputFileSp7);
             FileWriter outFileSp9 = new FileWriter(outputFileSp9)) {

            String line;
            while ((line = inFile.readLine()) != null) {
                List<Integer> data = new ArrayList<>();
                String[] tokens = line.split(" ");
                for (String token : tokens) {
                    data.add(Integer.parseInt(token));
                }
                int n = data.size();
                int[] dataArray = new int[n];
                for (int i = 0; i < n; i++) {
                    dataArray[i] = data.get(i);
                }

                Select selectp3 = new Select(3);
                Select selectp5 = new Select(5);
                Select selectp7 = new Select(7);
                Select selectp9 = new Select(9);

                int kth = (int) (k * n);
                long start, end, duration;

                start = System.nanoTime();
                selectp3.select(dataArray, kth);
                end = System.nanoTime();
                duration = end - start;
                outFileSp3.write(n + " " + selectp3.getComparisons() + " " + selectp3.getSwaps() + " " + duration + "\n");

                start = System.nanoTime();
                selectp5.select(dataArray, kth);
                end = System.nanoTime();
                duration = end - start;
                outFileSp5.write(n + " " + selectp5.getComparisons() + " " + selectp5.getSwaps() + " " + duration + "\n");

                start = System.nanoTime();
                selectp7.select(dataArray, kth);
                end = System.nanoTime();
                duration = end - start;
                outFileSp7.write(n + " " + selectp7.getComparisons() + " " + selectp7.getSwaps() + " " + duration + "\n");

                start = System.nanoTime();
                selectp9.select(dataArray, kth);
                end = System.nanoTime();
                duration = end - start;
                outFileSp9.write(n + " " + selectp9.getComparisons() + " " + selectp9.getSwaps() + " " + duration + "\n");
            }

            System.out.println("Results have been written.");

        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}