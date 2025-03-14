import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomDataGen {

    public static void main(String[] args) {
        String fileName = "randomData.txt";
        try (FileWriter outFile = new FileWriter(fileName)) {
            for (int n = 100; n <= 50000; n += 100) {
                for (int m = 1; m <= 50; m++) {
                    int[] randomKeys = generateRandomKeys(n);
                    for (int key : randomKeys) {
                        outFile.write(key + " ");
                    }
                    outFile.write("\n");
                }
            }
            System.out.println("Data has been written to " + fileName);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static int[] generateRandomKeys(int n) {
        int[] keys = new int[n];
        Random random = new Random();
        for (int i = 0; i < n; i++) {
            keys[i] = random.nextInt(2 * n);
        }
        return keys;
    }
}
