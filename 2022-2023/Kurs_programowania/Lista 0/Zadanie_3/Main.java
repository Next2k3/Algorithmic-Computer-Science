public class Main {
    public static int div(int n){
        int i=n/2;
        while(n%i!=0){
          i--;
        }
        return i;
    }
    public static void main(String[] args) {
        int n;
        for(int i=0;i<args.length;i++) {
            try {
                n = Integer.parseInt(args[i]);
                System.out.println(args[i]+" "+div(n));
            } catch (NumberFormatException ex) {
                System.out.println(args[i] + " nie jest liczba calkowita");
            }

        }
    }

}