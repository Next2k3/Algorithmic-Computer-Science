import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class SMain {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        List<Integer> data = new ArrayList<>();
        while (st.hasMoreTokens()) {
            data.add(Integer.parseInt(st.nextToken()));
        }

        int[] array = data.stream().mapToInt(Integer::intValue).toArray();

        Select select = new Select(5);
        int k = 4;
        int kthSmallest = select.select(array, k);
        System.out.println(k + "-th smallest number: " + kthSmallest);
        select.printStatistics();
    }
}
