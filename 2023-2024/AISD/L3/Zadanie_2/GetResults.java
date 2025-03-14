import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class GetResults {

    public static void main(String[] args) {
        String inputFile = "randomData.txt";
        String outputFileRSk1_10 = "RSresults_k_1_10.txt";
        String outputFileRSk9_10 = "RSresults_k_9_10.txt";
        String outputFileRSk1_2 = "RSresults_k_1_2.txt";
        String outputFileSk1_10 = "Sresults_k_1_10.txt";
        String outputFileSk9_10 = "Sresults_k_9_10.txt";
        String outputFileSk1_2 = "Sresults_k_1_2.txt";
        double k1_10 = 0.1;
        double k9_10 = 0.9;
        double k1_2 = 0.5;

        try (BufferedReader inFile = new BufferedReader(new FileReader(inputFile));
             FileWriter outFileRSk1_10 = new FileWriter(outputFileRSk1_10);
             FileWriter outFileRSk9_10 = new FileWriter(outputFileRSk9_10);
             FileWriter outFileRSk1_2 = new FileWriter(outputFileRSk1_2);
             FileWriter outFileSk1_10 = new FileWriter(outputFileSk1_10);
             FileWriter outFileSk9_10 = new FileWriter(outputFileSk9_10);
             FileWriter outFileSk1_2 = new FileWriter(outputFileSk1_2)) {

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

                RandomizedSelect randomizedSelectk1_10 = new RandomizedSelect();
                RandomizedSelect randomizedSelectk9_10 = new RandomizedSelect();
                RandomizedSelect randomizedSelectk1_2 = new RandomizedSelect();
                Select selectk1_10 = new Select(5);
                Select selectk9_10 = new Select(5);
                Select selectk1_2 = new Select(5);
                int k1 = (int) (k1_10 * n);
                int k2 = (int) (k9_10 * n);
                int k3 = (int) (k1_2 * n);

                randomizedSelectk1_10.randomizedSelect(dataArray, k1);
                outFileRSk1_10.write(n + " " + randomizedSelectk1_10.getComparisons() + " " + randomizedSelectk1_10.getSwaps() + "\n");
                randomizedSelectk9_10.randomizedSelect(dataArray, k2);
                outFileRSk9_10.write(n + " " + randomizedSelectk9_10.getComparisons() + " " + randomizedSelectk9_10.getSwaps() + "\n");
                randomizedSelectk1_2.randomizedSelect(dataArray, k3);
                outFileRSk1_2.write(n + " " + randomizedSelectk1_2.getComparisons() + " " + randomizedSelectk1_2.getSwaps() + "\n");

                selectk1_10.select(dataArray, k1);
                outFileSk1_10.write(n + " " + selectk1_10.getComparisons() + " " + selectk1_10.getSwaps() + "\n");
                selectk9_10.select(dataArray, k2);
                outFileSk9_10.write(n + " " + selectk9_10.getComparisons() + " " + selectk9_10.getSwaps() + "\n");
                selectk1_2.select(dataArray, k3);
                outFileSk1_2.write(n + " " + selectk1_2.getComparisons() + " " + selectk1_2.getSwaps() + "\n");
            }

            System.out.println("Results have been written.");

        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}
