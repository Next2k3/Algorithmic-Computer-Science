
public class WierszTrojkataPascala {
    private int[] wiersz;
    public WierszTrojkataPascala(int n) throws IllegalArgumentException {
        if (n < 0) {
            throw new IllegalArgumentException(n +" - Nieprawidłowy numer wiersza.");
        }
        wiersz =new int[n+1];
        wiersz[0]=1;
        for (int i = 1; i <= n; i++) {
            for (int j = i; j >= 1; j--) {
                wiersz[j] += wiersz[j-1];
            }
        }
    }
    int wspolczynnik(int m) throws IllegalArgumentException {
        if (m < 0 || m > wiersz.length - 1) {
            throw new IllegalArgumentException("Numer współczynnika poza zakresem.");
        }
        return wiersz[m];
    }
}
