import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class RandGen {

    public static List<Integer> generateRandomKeys(int n) {
        List<Integer> keys = new ArrayList<>();
        Random rand = new Random();

        for (int i = 0; i < n; ++i) {
            keys.add(rand.nextInt(2 * n));
        }

        return keys;
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java RandGen <array_size>");
            System.exit(1);
        }

        int n = Integer.parseInt(args[0]);
        if (n <= 0) {
            System.err.println("Array size must be a positive integer.");
            System.exit(1);
        }

        List<Integer> randomKeys = generateRandomKeys(n);
        for (int key : randomKeys) {
            System.out.print(key + " ");
        }
        System.out.println();
    }
}
