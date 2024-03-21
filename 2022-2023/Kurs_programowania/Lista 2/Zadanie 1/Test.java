public class Test {
    public static void main(String[] args){
        if (args.length < 1) {
            System.out.println("Podaj co najmniej jeden argument.");
            return;
        }
        try{
            int n = Integer.parseInt(args[0]);
            WierszTrojkataPascala trojkat = new WierszTrojkataPascala(n);
            for (int i = 1; i < args.length; i++) {
                try {
                    int m = Integer.parseInt(args[i]);
                    int wsp = trojkat.wspolczynnik(m);
                    System.out.println(m + " - " + wsp);
                } catch (NumberFormatException e) {
                    System.out.println(args[i] + " - nieprawidłowa dana");
                } catch (IllegalArgumentException e) {
                    System.out.println(args[i] + " - " + e.getMessage());
                }
            }
        } catch (NumberFormatException e) {
            System.out.println(args[0] + " - nieprawidłowy numer wiersza");
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }

    }
}
