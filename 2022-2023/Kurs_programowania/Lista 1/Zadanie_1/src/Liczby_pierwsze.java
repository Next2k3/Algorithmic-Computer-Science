public class Liczby_pierwsze {
    private int pierwsze[];
    public Liczby_pierwsze(int n){
        boolean zlozone[]=new boolean[n+1];
        int ilosc=0;
        for(int i=2;i<=n;i++){
            if(!zlozone[i]){
                ilosc++;
                for(int j=i*i;j<=n;j+=i){
                    zlozone[j]=true;
                }
            }
        }
        pierwsze = new int[ilosc];
        int indeks=0;
        for(int i=2;i<=n;i++){
            if(!zlozone[i]){
                pierwsze[indeks]=i;
                indeks++;
            }
        }
    }
    int liczba(int m){
        if(m<0 || m>=pierwsze.length){
            System.out.println(m+" - liczba spoza zakresu");
            return -1;
        }
        return pierwsze[m];
    }
}
