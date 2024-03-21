import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

import java.util.Random;

public class Symulacja extends Application {
    private int n;  // liczba kolumn
    private int m;  // liczba wierszy
    private int k;  // opóźnienie w ms
    private double p;  // prawdopodobieństwo zmiany koloru na losowy
    private Rectangle[][] fields;  // tablica prostokątów
    private boolean[][] suspendedThreads;  // zawieszone wątki
    private Thread[][] thread;  // tablica wątków
    private Random random;

    @Override
    public void start(Stage stage) {
        // Sprawdzenie liczby argumentów
        if (getParameters().getRaw().size() != 4) {
            System.out.println("Nieprawidłowa liczba argumentów. Podaj 4 argumenty: <n> <m> <k> <p>");
            Platform.exit();
            return;
        }

        wczytajparametry();

        GridPane gridPane = new GridPane();
        gridPane.setAlignment(Pos.CENTER);
        fields = new Rectangle[n][m];
        random = new Random();
        suspendedThreads = new boolean[n][m];
        thread = new Thread[n][m];

        int s = 15;  // rozmiar kwadratów

        // Tworzenie siatki prostokątów
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                Rectangle rectangle = new Rectangle(s, s);
                rectangle.setFill(getRandomColor());
                fields[i][j] = rectangle;
                gridPane.add(rectangle, i, j);

                int finalI = i;
                int finalJ = j;
                rectangle.setOnMouseClicked(e -> toggleThreadState(finalI, finalJ));
            }
        }

        Scene scene = new Scene(gridPane, n * s, m * s);
        stage.setScene(scene);
        stage.setTitle("Symulacja");
        stage.setOnCloseRequest(e -> {
            Platform.exit();
            System.exit(0);
        });
        stage.show();

        // Uruchamianie wątków
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                final int row = i;
                final int col = j;

                thread[i][j] = new Thread(() -> {
                    while (true) {
                        try {
                            Thread.sleep(getRandomDelay());
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                        if (!suspendedThreads[row][col]) {
                            Platform.runLater(() -> {
                                System.out.println("Start: " + thread[row][col].getId());
                                if (random.nextDouble() < p) {
                                    fields[row][col].setFill(getRandomColor());
                                } else {
                                    fields[row][col].setFill(getAverageNeighborColor(row, col));
                                }
                                System.out.println("End: " + thread[row][col].getId());
                            });
                        }
                    }
                });
                thread[i][j].start();
            }
        }
    }

    // Przełączanie stanu zawieszenia wątku dla konkretnego prostokąta
    private void toggleThreadState(int row, int col) {
        suspendedThreads[row][col] = !suspendedThreads[row][col];
    }

    // Obliczanie średniego koloru sąsiadów prostokąta
    private Color getAverageNeighborColor(int row, int col) {
        double red = 0.0;
        double green = 0.0;
        double blue = 0.0;

        int newrow;
        int newcol;

        newrow = (row - 1 + n) % n;
        red += ((Color) fields[newrow][col].getFill()).getRed();
        green += ((Color) fields[newrow][col].getFill()).getGreen();
        blue += ((Color) fields[newrow][col].getFill()).getBlue();

        newrow = (row + 1) % n;
        red += ((Color) fields[newrow][col].getFill()).getRed();
        green += ((Color) fields[newrow][col].getFill()).getGreen();
        blue += ((Color) fields[newrow][col].getFill()).getBlue();

        newcol = (col - 1 + m) % m;
        red += ((Color) fields[row][newcol].getFill()).getRed();
        green += ((Color) fields[row][newcol].getFill()).getGreen();
        blue += ((Color) fields[row][newcol].getFill()).getBlue();

        newcol = (col + 1) % m;
        red += ((Color) fields[row][newcol].getFill()).getRed();
        green += ((Color) fields[row][newcol].getFill()).getGreen();
        blue += ((Color) fields[row][newcol].getFill()).getBlue();

        double averageRed = red / 4.0;
        double averageGreen = green / 4.0;
        double averageBlue = blue / 4.0;

        return Color.color(averageRed, averageGreen, averageBlue);
    }

    // Generowanie losowego opóźnienia dla wątku
    private long getRandomDelay() {
        double min = 0.5 * k;
        double max = 1.5 * k;
        return (long) (min + (max - min) * random.nextDouble());
    }

    // Generowanie losowego koloru
    private Color getRandomColor() {
        double red = random.nextDouble();
        double green = random.nextDouble();
        double blue = random.nextDouble();
        return new Color(red, green, blue, 1.0);
    }

    // Wczytywanie parametrów
    private void wczytajparametry() {
        try {
            n = Integer.parseInt(getParameters().getRaw().get(0));
            m = Integer.parseInt(getParameters().getRaw().get(1));
            k = Integer.parseInt(getParameters().getRaw().get(2));
            p = Double.parseDouble(getParameters().getRaw().get(3));
        } catch (NumberFormatException e) {
            System.out.println("Nieprawidłowe argumenty. Upewnij się, że podane argumenty są liczbami.");
            Platform.exit();
        }
        if (p < 0 || p > 1) {
            System.out.println("Nieprawidłowy argument <p>. Upewnij się, że argument <p> jest liczbą z przedziału <0,1>.");
            Platform.exit();
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}