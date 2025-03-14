import java.io.FileWriter;
import java.io.IOException;
import java.util.List;

public class Main {
    public static void main(String[] args) {

        String outputFileAsc = "outputAsc.txt";
        String outputFileRand = "outputRand.txt";

        try (FileWriter outputAsc = new FileWriter(outputFileAsc);
             FileWriter outputRand = new FileWriter(outputFileRand)) {

            for (int size = 10000; size <= 100000; size += 10000) {

                for (int j = 0; j < 20; j++) {
                    RedBlackBinarySearchTree bstAsc = new RedBlackBinarySearchTree();
                    RedBlackBinarySearchTree bstRand = new RedBlackBinarySearchTree();

                    List<Integer> keysToAddAsc = Generator.ascendingKeys(size);
                    for (Integer key : keysToAddAsc) {
                        bstAsc.insert(key);
                    }

                    List<Integer> keysToDeleteAsc = Generator.randomKeys(size);
                    for (Integer key : keysToDeleteAsc) {
                        bstAsc.delete(key);
                    }

                    List<Integer> keysToAddRand = Generator.randomKeys(size);
                    for (Integer key : keysToAddRand) {
                        bstRand.insert(key);
                    }

                    List<Integer> keysToDeleteRand = Generator.randomKeys(size);
                    for (Integer key : keysToDeleteRand) {
                        bstRand.delete(key);
                    }

                    outputAsc.write(size + " " + bstAsc.getComparisons() + " " + bstAsc.getReads() + " " + bstAsc.getAssignments() + " " + bstAsc.height() + "\n");
                    outputAsc.flush();
                    outputRand.write(size + " " + bstRand.getComparisons() + " " + bstRand.getReads() + " " + bstRand.getAssignments() + " " + bstRand.height() + "\n");
                    outputRand.flush();
                    System.out.println(size);
                    bstAsc.resetCounters();
                    bstRand.resetCounters();
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
