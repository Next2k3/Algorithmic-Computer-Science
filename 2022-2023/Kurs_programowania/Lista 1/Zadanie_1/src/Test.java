public class Test {
    public static void main(String[] args){
        if(args.length<2){
            System.out.println("Za mało argumentów.");
            return;
        }
        int n;
        try {
            n = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println(args[0] + " - Nieprawidłowy zakres");
            return;
        }
        if (n < 2) {
            System.out.println(n + " - Nieprawidłowy zakres");
            return;
        }
        Liczby_pierwsze liczby_parametry =new Liczby_pierwsze(n);
        for(int i=1;i< args.length;i++){
            int argument;
            try{
                argument = Integer.parseInt(args[i]);
            }catch(NumberFormatException e){
                System.out.println(args[i] + " - nieprawidłowa dana");
                continue;
            }
            try{
                int pierwsze = liczby_parametry.liczba(argument);
                if(pierwsze!=-1) {
                    System.out.println(argument + " - " + pierwsze);
                }
            }catch(IllegalArgumentException e){
                System.out.println(argument + " - " + e.getMessage());
            }
        }

    }


}
