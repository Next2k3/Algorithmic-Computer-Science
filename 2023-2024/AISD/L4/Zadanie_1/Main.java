import java.util.List;

public class Main {
	public static int size = 50;
	public static List<Integer> keysToAdd;
	public static void main(String[] args){
		if(args.length != 1) {
			System.err.println("Usage: java Main <data_type>");
			System.exit(1);
		}
		
		BinarySearchTree tree = new BinarySearchTree();
		
		String dataType = args[0];
		
		if(dataType.equals("asc")) {
      	keysToAdd = Generator.ascendingKeys(size);
      }
      else if(dataType.equals("rand")) {
         keysToAdd = Generator.randomKeys(size);
     	}
      else {
         System.err.println("data type must be either asc or rand");
         System.exit(1);
     	}

      List<Integer> keysToDelete = Generator.randomKeys(size);
      

      for(Integer key : keysToAdd) {
         tree.insert(key);
         tree.printTree();
      }
      for(Integer key : keysToDelete) {
         tree.delete(key);
         tree.printTree();
      }
	
	}
}
