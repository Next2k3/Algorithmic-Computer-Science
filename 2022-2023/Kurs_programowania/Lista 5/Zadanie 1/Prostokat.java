import javafx.event.EventHandler;
import javafx.scene.control.Button;
import javafx.scene.control.ColorPicker;
import javafx.scene.control.ContextMenu;
import javafx.scene.control.CustomMenuItem;
import javafx.scene.control.MenuItem;
import javafx.scene.control.Slider;
import javafx.scene.control.Menu;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.ScrollEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.transform.Rotate;

import java.io.*;

public class Prostokat extends Rectangle implements Serializable {
    /** Podstawowy konstruktor
     * @param x deklarowana współrzędna "x" obiektu
     * @param y deklarowana współrzędna "y" obiektu
     * @param width deklarowana szerokosc obiektu
     * @param height deklarowana wysokosc obiektu
     * @param color deklarowany kolor obiektu
     */
    public Prostokat(double x, double y,double width,double height,Color color){
        super(x,y,width,height);
        setFill(color);
        setOnMouseClicked(new Prostokat.ProstokatEventHandler());
        setOnMouseDragged(new Prostokat.ProstokatEventHandler());
        setOnScroll(new ProstokatScrollHandler());
    }

    /**
     * metoda sprawdzajaca czy zdarzenie dotyczy obiektu
     * @param x deklarowana wspolrzedna "x" dla zdarzenia
     * @param y deklarowana wspolrzedna "y" dla zdarzeania
     * @return bool
     */
    public boolean isHit(double x, double y) {

        return getBoundsInLocal().contains(x,y);
    }

    /**
     *  Metoda zmieniajaca wspolrzedna "x" obiektu o parametr x
     * @param x parametr o ktory zmieni sie wsporzedna "x" obiektu
     */
    public void addX(double x) {
        setX(getX()+x);
    }

    /**
     *Metoda zmieniajaca wspolrzedna "y" obiektu o parametr y
     * @param y parametr o ktory zmieni sie wsporzedna "y" obiektu
     */
    public void addY(double y) {
        setY(getY()+y);
    }

    /**
     *  Metoda modyfikuje szerokosc obiektu o zadany parametr
     * @param w parametr o ktory zmieni sie szerokosc obiektu
     */
    public void addWidth(double w) {
        setWidth(getWidth()+w);
    }

    /**
     *  Metoda zmieniajaca wysokosc prosotokata o parametr
     * @param h parametr o ktory zmieni sie wysokosc obiektu
     */
    public void addHeight(double h) {
        setHeight(getHeight()+h);
    }

    /**
     * Metoda obracajaca prostokat
     * @param angle katem pod jakim zostanie obrocony
     * @param x wspolrzedna "x" punktu
     * @param y wspolrzedna "y" punktu
     */
    public void doRotate(double angle,double x,double y ){
        getTransforms().add(new Rotate(angle,x,y));
    }

    /**
     * Implementacja scrollowania
     */
    class ProstokatEventHandler implements EventHandler<MouseEvent>, Serializable {

        Prostokat prostokat;
        private double x;
        private double y;

        /**
         *Jesli nacisnelismy na prostokat
         */
        private void doMove(MouseEvent event) {

            double dx = event.getX() - x;
            double dy = event.getY() - y;

            if (prostokat.isHit(x, y)) {
                prostokat.addX(dx);
                prostokat.addY(dy);
            }
            x += dx;
            y += dy;
        }
        @Override
        public void handle(MouseEvent event) {
                prostokat = (Prostokat) event.getSource();

                if (event.getEventType() == MouseEvent.MOUSE_CLICKED) {
                    if(event.getButton()==MouseButton.PRIMARY) {
                        x = event.getX();
                        y = event.getY();
                    }else{
                        ContextMenu menuedycja = new ContextMenu();
                        ColorPicker colorPicker = new ColorPicker();
                        Slider slider = new Slider(0.0,360.0,0.0);

                        Menu rotatemenu = new Menu("Rotacja");
                        Menu pickermenu = new Menu("Kolor");
                        Menu zapiszmenu = new Menu("Zapisz");
                        MenuItem usun = new MenuItem("Usuń");

                        CustomMenuItem pickeritem = new CustomMenuItem(colorPicker);
                        pickeritem.setHideOnClick(false);
                        MenuItem rotateitem = new MenuItem(null,slider);

                        GridPane gridPane = new GridPane();
                        javafx.scene.control.Label label = new javafx.scene.control.Label("Podaje nazwe pliku:");
                        javafx.scene.control.TextField textField = new javafx.scene.control.TextField();
                        textField.setPromptText("nazwa ");
                        javafx.scene.control.Button button = new Button("Zapisz");

                        gridPane.add(label,0,0);
                        gridPane.add(textField,0,1);
                        gridPane.add(button,0,2);

                        MenuItem zapiszitem = new MenuItem(null,gridPane);

                        pickermenu.getItems().add(pickeritem);
                        rotatemenu.getItems().add(rotateitem);
                        zapiszmenu.getItems().add(zapiszitem);

                        menuedycja.getItems().addAll(pickermenu,rotatemenu,zapiszmenu,usun);
                        menuedycja.show(prostokat,event.getScreenX(),event.getScreenY());

                        button.setOnAction(event2 -> {
                            String nazwa;
                            String objekt;
                            objekt=prostokat.toString();
                            nazwa = textField.getText();
                            nazwa += ".txt";
                            try {
                                FileOutputStream fileOut = new FileOutputStream(nazwa);
                                PrintWriter writer = new PrintWriter(fileOut);

                                writer.println(objekt);

                                writer.close();
                                fileOut.close();
                            } catch(IOException i) {
                                i.printStackTrace();
                            }
                        });
                        usun.setOnAction(event1 -> ((Pane) getParent()).getChildren().remove(prostokat));
                        colorPicker.setOnAction(event1 -> setFill(colorPicker.getValue()));
                        slider.valueProperty().addListener((obs,oldvalue,newvalue)-> doRotate((double) newvalue-(double)oldvalue,getX()+getWidth()/2,getY()+getHeight()/2));

                    }
                }
                if (event.getEventType() == MouseEvent.MOUSE_DRAGGED) {
                    if(event.getButton()==MouseButton.PRIMARY) {
                        doMove(event);
                    }
                }
        }
    }

    /**
     *Handler scrolla dla klasy Prosotkat
     */
    static class ProstokatScrollHandler implements EventHandler<ScrollEvent>{

        Prostokat prostokat;

        /**
         *Metoda odpowiadajaca za zmiane rozmiaru obiektu wzaleznosci od zdarzenia
         */
        private void doScale(ScrollEvent e) {

            double x = e.getX();
            double y = e.getY();

            if (prostokat.isHit(x, y)) {
                prostokat.addWidth(e.getDeltaY()*0.2);
                prostokat.addHeight(e.getDeltaY()*0.2);
            }
        }

        @Override
        public void handle(ScrollEvent event) {

            prostokat = (Prostokat) event.getSource();
            if (event.getEventType()==ScrollEvent.SCROLL){
                doScale(event);
            }
        }
    }
}
