import java.util.ArrayList;
import java.util.List;
import java.util.Collections;
import java.util.Random;

public class SortedArray {

    public static List<Integer> generateRandomSortedKeys(int n) {
        List<Integer> keys = new ArrayList<>();
        Random rand = new Random();

        for (int i = 0; i < n; ++i) {
            keys.add(rand.nextInt(2 * n));
        }

        Collections.sort(keys);

        return keys;
    }
}
