public class TrojkatPascala {
    public static String TrojkatPascala(int size) {
        if (size < 1) {
            throw new IllegalArgumentException("Rozmiar poza zakresu");
        }

        long[][] trojkat = new long[size][];
        trojkat[0] = new long[]{1};

        for (int i = 1; i < size; i++) {
            long[] wiersz = new long[i + 1];
            wiersz[0] = 1;
            wiersz[i] = 1;
            for (int j = 1; j < i; j++) {
                wiersz[j] = trojkat[i - 1][j - 1] + trojkat[i - 1][j];
            }

            trojkat[i] = wiersz;
        }

        int maxelement = Long.toString(trojkat[size-1][size/2]).length();
        String wynik ="";
        for(int i=0;i<size;i++){
            for(int j=0;j<(size-i-1)*(maxelement+2);j++){
                wynik+=" ";
            }
            for(int j=0;j<=i;j++){
                int x=(maxelement-Long.toString(trojkat[i][j]).length())/2;
                for(int k=0;k<x+1;k++){
                    wynik+=" ";
                }
                if(Long.toString(trojkat[i][j]).length()%2==0)wynik+=" ";
                wynik+=Long.toString(trojkat[i][j]);
                for(int k=0;k<x+1;k++) {
                    wynik += " ";
                }
                for(int k=0;k<maxelement+2;k++){
                    wynik+=" ";
                }
            }
            wynik+="\n";
        }
        return wynik;
    }
}
