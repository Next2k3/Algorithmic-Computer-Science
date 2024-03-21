import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.scene.shape.Shape;
import javafx.stage.Stage;

import java.io.*;
import java.util.Arrays;

/**
 * Klasa główna odpowiadajaca za program
 */
public class Test extends Application {
    private double[] points;
    private double clickCount=0;
    private String type="O";
    private Pane gr;
    private Prostokat prostokat;
    private Okrag okrag;

    private Wielokat wielokat;
    Color color=Color.BLACK;

    /**
     * Główna funkcja wywołujaca program
     * @param args argumenty przy wywolaniu programu
     */
    public static void main(String[] args){

        launch(args);
    }
    @Override
    public void start(Stage stage){
        BorderPane pane = new BorderPane();
        gr = new Pane();
        MenuBar menuBar = new MenuBar();

        Menu plik = new Menu("Plik");
        Menu figury = new Menu("Figury");
        Menu info =new Menu("Info");

        Menu wczytaj = new Menu("Wczytaj");
        MenuItem wylacz = new MenuItem("Wyłącz");

        MenuItem okrag = new MenuItem("Okrag");
        MenuItem prostokat = new MenuItem("Prostokat");
        MenuItem wielokat = new MenuItem("Wielokat");

        MenuItem o_programie = new MenuItem("O programie");

        info.getItems().addAll(o_programie);

        o_programie.setOnAction(event ->{
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Edytor Peepoblush");
            alert.setHeaderText("Aplikacja do rysowania figur");
            alert.setContentText("""
                    Nazwa: Edytor peepoblush
                    Przeznaczenie: Tworzenie i modyfikowanie figur
                    Autor: Paweł Krzyszczak
                    Instrukja użytkowanika:
                            1.Menu główne:
                                -Plik:
                                    -wczytaj - wczytywanie figury z pliku o podanej\s
                                             nazwie
                                    -wylacz - wylacza program
                                -Figury:
                                    -Okrag - pozwala na tworzenie okregow
                                             przez klikniecie dwoch pustych punktow
                                    -Prostokat - pozwala na tworzenie prosotokatow
                                             przez klikniecie dwoch pustych punktow
                                    -Wielokat - pozwala na tworzenie wielokatow
                                             przez klikniecie dowolnej liczy pustych
                                             punktow lewym przycikiem i zakceptowanie
                                             przez uzycie prawego przycisku w puste miejsce
                                -info:
                                    -ogolne informacje o programie
                            2.Menu edycji
                            (aktywowane przez prawy przycisk uzyty na figurze):
                                -Kolor - modyfikuje kolor figury na wybrany
                                -Rotacja - pozwala na obrucenie figury za pomoca
                                         suwaka
                                -Zapisz - pozwala na zapisanie figury w plik o podanej
                                         nazwie
                                -usun - usuwa wskazana figure
                    """);
            alert.showAndWait();
        });

        GridPane gridPane = new GridPane();
        Label label = new Label("Podaje nazwe pliku:");
        TextField textField = new TextField();
        textField.setPromptText("nazwa ");
        Button button = new Button("Wczytaj");

        gridPane.add(label,0,0);
        gridPane.add(textField,0,1);
        gridPane.add(button,0,2);

        MenuItem wczytajitem = new MenuItem(null,gridPane);

        button.setOnAction(event -> {
            String nazwa;

            nazwa=textField.getText()+".txt";
            try {
                FileInputStream fileIn = new FileInputStream(nazwa);
                BufferedReader reader = new BufferedReader(new InputStreamReader(fileIn));

                String str = reader.readLine();
                gr.getChildren().add(parseShapeFromString(str));


                reader.close();
                fileIn.close();
            }catch (IOException i) {
                i.printStackTrace();
            }
        });
        okrag.setOnAction(actionEvent ->{
            type="O";
            clickCount=0;
        });
        prostokat.setOnAction(actionEvent -> {
            type="P";
            clickCount=0;
        });
        wielokat.setOnAction(actionEvent -> {
            type="W";
            clickCount=0;
        });
        wylacz.setOnAction(event -> System.exit(0));
        wczytaj.getItems().add(wczytajitem);

        plik.getItems().addAll(wczytaj,wylacz);

        figury.getItems().addAll(okrag,prostokat,wielokat);

        menuBar.getMenus().addAll(plik,figury,info);

        pane.setCenter(gr);
        pane.setTop(menuBar);

        gr.setOnMouseClicked(this::handleMouseClick);

        Scene scene = new Scene(pane,400,400);
        stage.setScene(scene);
        stage.setTitle("Edytor peepoblush");
        stage.show();
    }

    /**
     * fukcja odpowiadajaca za utworzenie odpowidniej figury zgodnie z parametrami
     * @param shapeString parametr opisujacy rodzaj i wlasciwosci figury
     * @return zwraca obiekt bedacy dziedziczacy po Shape
     */
    public static Shape parseShapeFromString(String shapeString) {
        String shapetype=shapeString.replaceAll("\\[.*?]", "");
        if (shapeString.startsWith("Circle")) {
            String shape = shapeString.replace("Circle", "");
            String[] items = shape.split(", ");
            String[] result = new String[items.length];
            for (int i = 0; i < items.length; i++) {
                String item = items[i];
                if (i == items.length - 1) {
                    // Usuń znak ']' z ostatniego elementu
                    item = item.replaceAll("]", "");
                }
                result[i] = item.substring(item.indexOf("=") + 1);
                System.out.println(result[i]);
            }
            double centerX = Double.parseDouble(result[0]);
            double centerY = Double.parseDouble(result[1]);
            double radius = Double.parseDouble(result[2]);
            Color color1 = Color.valueOf(result[3]);
            return new Okrag(centerX, centerY, radius,color1);
        } else if (shapeString.startsWith("Rectangle")) {
            String shape = shapeString.replace("Rectangle", "");
            String[] items = shape.split(", ");
            String[] result = new String[items.length];
            for (int i = 0; i < items.length; i++) {
                String item = items[i];
                if (i == items.length - 1) {
                    item = item.replaceAll("]", "");
                }
                result[i] = item.substring(item.indexOf("=") + 1);
                System.out.println(result[i]);
            }
            double x = Double.parseDouble(result[0]);
            double y = Double.parseDouble(result[1]);
            double width = Double.parseDouble(result[2]);
            double height = Double.parseDouble(result[3]);
            Color fill = Color.valueOf(result[4]);
            return new Prostokat(x,y,width,height,fill);
        } else if (shapeString.startsWith("Polygon")) {
            int startIndex = shapeString.indexOf("[") + 1;
            int endIndex = shapeString.indexOf("]");
            String copiedText = shapeString.substring(startIndex, endIndex);
            copiedText=copiedText.replace("points=[","");
            String[] parts = copiedText.split(", ");
            double[] points = new double[parts.length];

            for (int i = 0; i < parts.length; i++) {
                points[i] = Double.parseDouble(parts[i]);
            }
            int fillIndex = shapeString.indexOf("fill=");
            endIndex = shapeString.indexOf("]", fillIndex);
            String fillValue = shapeString.substring(fillIndex + 5, endIndex);
            Color color1 = Color.valueOf(fillValue);
            return new Wielokat(points,color1);
        }else {
            throw new IllegalArgumentException("Unknown shape type: " + shapetype);
        }
    }

    /**
     * Funkcja odpowiadajaca za zdarzenia zwiazane z działaniem myszy na applikacji
     * @param event zdarzenie dotyczace programu
     */
    public void handleMouseClick(MouseEvent event) {
        if (event.getTarget() instanceof Pane && event.getTarget() == gr) {

            if (event.getButton() == MouseButton.PRIMARY) {
                clickCount++;
                switch (type) {
                    case "O" -> {
                        if (clickCount == 1) {
                            double mouseX = event.getX();
                            double mouseY = event.getY();

                            okrag = new Okrag(mouseX, mouseY, 0, color);
                            gr.getChildren().add(okrag);
                        } else if (clickCount == 2) {
                            double centerX = okrag.getCenterX();
                            double centerY = okrag.getCenterY();

                            double radius = Math.sqrt(Math.pow(event.getX() - centerX, 2) + Math.pow(event.getY() - centerY, 2));
                            Okrag okrag1 = new Okrag(centerX, centerY, radius, color);
                            gr.getChildren().add(okrag1);
                            clickCount = 0;
                        }
                    }
                    case "P" -> {
                        if (clickCount == 1) {
                            double mouseX = event.getX();
                            double mouseY = event.getY();

                            prostokat = new Prostokat(mouseX, mouseY, 0, 0, color);
                            gr.getChildren().add(prostokat);
                        } else if (clickCount == 2) {
                            double mouseX = event.getX();
                            double mouseY = event.getY();

                            double X = prostokat.getX();
                            double Y = prostokat.getY();

                            if (X - mouseX > 0) {
                                double x = X;
                                X = mouseX;
                                mouseX = x;
                            }
                            if (Y - mouseY > 0) {
                                double y = Y;
                                Y = mouseY;
                                mouseY = y;
                            }

                            double width = mouseX - X;
                            double height = mouseY - Y;


                            Prostokat prostokat1 = new Prostokat(X, Y, width, height, color);
                            gr.getChildren().add(prostokat1);
                            clickCount = 0;
                        }
                    }
                    case "W" -> {
                        if (clickCount == 1) {
                            points = new double[2];
                            points[0] = event.getX();
                            points[1] = event.getY();
                            wielokat = new Wielokat(points,color);
                        } else {
                            points = Arrays.copyOf(points, points.length + 2);
                            points[points.length - 2] = event.getX();
                            points[points.length - 1] = event.getY();
                            gr.getChildren().remove(wielokat);
                            wielokat = new Wielokat(points, color);
                            gr.getChildren().add(wielokat);
                        }
                        clickCount++;
                    }
                    default -> {
                    }
                }

            } else if (type.equals("W") && points != null && clickCount>3) {
                clickCount = 0;
                points = new double[0];
            }
        }
    }
}

