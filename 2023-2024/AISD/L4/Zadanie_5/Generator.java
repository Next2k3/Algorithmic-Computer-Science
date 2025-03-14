import java.util.Collections;
import java.util.Random;
import java.util.Random;
import java.util.ArrayList;
import java.util.List;

public class Generator {
    public static List<Integer> randomKeys(int n) {
        List<Integer> keys = new ArrayList<Integer>();
        Random rand = new Random();

        for (int i = 0; i < n; i++) {
            keys.add(rand.nextInt(2*n));
        }
        return keys;
    }

    public static List<Integer> ascendingKeys(int n) {
        List<Integer> keys = new ArrayList<Integer>();
        Random rand = new Random();

        for (int i = 0; i < n; i++) {
            keys.add(rand.nextInt(2*n));
        }

        Collections.sort(keys);

        return keys;
    }

}