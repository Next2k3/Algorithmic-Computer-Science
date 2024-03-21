import javafx.event.EventHandler;
import javafx.scene.control.*;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.ScrollEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

import java.io.*;

/**
 * Klasa generujaca obiekt Okrag
 */
public class Okrag extends Circle implements Serializable {
    /**
     * Główny konstruktor klasy
     * @param x deklarowana współrzędna "x" obiektu
     * @param y deklarowana współrzędna "y" obiektu
     * @param radius deklarowany promien obiektu
     * @param color deklarowana kolor obiektu
     */
    public Okrag(double x,double y,double radius,Color color){
        super(x,y,radius);
        setFill(color);
        setOnMouseClicked(new Okrag.OkragEventHandler());
        setOnMouseDragged(new Okrag.OkragEventHandler());
        setOnScroll(new OkragScrollHandler());
    }

    /**
     * metoda sprawdzajaca czy zdarzenie dotyczy obiektu
     * @param x deklarowana współrzędna "x"
     * @param y deklarowana współrzędna "y"
     * @return zwraca bool
     */
    public boolean isHit(double x,double y){
        return getBoundsInLocal().contains(x,y);
    }

    /**
     * Metoda odpowiadajca za zmiane parametru "x" obiektu
     * @param x parametr o który zostanie zieniona wspolrzedna "x"
     */
    public void addX(double x){
        setCenterX(getCenterX()+x);
    }
    /**
     * Metoda odpowiadajca za zmiane parametru "y" obiektu
     * @param y parametr o który zostanie zieniona wspolrzedna "y"
     */
    public void addY(double y){
        setCenterY(getCenterY()+y);
    }
    /**
     * Metoda odpowiadajca za zmiane promienia obiektu
     * @param r parametr o który zostanie zieniona promien
     */
    public void addradius(double r){
        setRadius(getRadius()+r);
    }

    /**
     * Implementacja przesuwania
     */
    class OkragEventHandler implements EventHandler<MouseEvent>,Serializable{
        Okrag okrag;
        private double x;
        private double y;

        /**
         * Jesli nacisniesz na Okrag
         */
        private  void doMove(MouseEvent event) {
                double dx = event.getX() - x;
                double dy = event.getY() - y;
                if (okrag.isHit(x, y)) {
                    okrag.addX(dx);
                    okrag.addY(dy);
                }
                x += dx;
                y += dy;
        }
        @Override
        public void handle(MouseEvent event) {
                okrag = (Okrag) event.getSource();
                if (event.getEventType() == MouseEvent.MOUSE_CLICKED) {
                    if(event.getButton()== MouseButton.PRIMARY) {
                        x = event.getX();
                        y = event.getY();
                    }else{
                        ContextMenu menuedycja = new ContextMenu();
                        ColorPicker colorPicker = new ColorPicker();

                        Menu pickermenu = new Menu("Kolor");
                        Menu zapiszmenu = new Menu("Zapisz");
                        MenuItem usun = new MenuItem("Usuń");

                        CustomMenuItem pickeritem = new CustomMenuItem(colorPicker);
                        pickeritem.setHideOnClick(false);

                        GridPane gridPane = new GridPane();
                        Label label = new Label("Podaje nazwe pliku:");
                        TextField textField = new TextField();
                        textField.setPromptText("nazwa ");
                        Button button = new Button("Zapisz");

                        gridPane.add(label,0,0);
                        gridPane.add(textField,0,1);
                        gridPane.add(button,0,2);

                        MenuItem zapiszitem = new MenuItem(null,gridPane);

                        pickermenu.getItems().add(pickeritem);
                        zapiszmenu.getItems().add(zapiszitem);

                        menuedycja.getItems().addAll(pickermenu,zapiszmenu,usun);
                        menuedycja.show(okrag,event.getScreenX(),event.getScreenY());

                        button.setOnAction(event2 -> {
                            String nazwa;
                            String objekt;

                            nazwa = textField.getText();
                            nazwa += ".txt";

                            objekt=okrag.toString();
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
                        usun.setOnAction(event1 -> ((Pane) getParent()).getChildren().remove(okrag));
                        colorPicker.setOnAction(event1 -> setFill(colorPicker.getValue()));
                    }
                }
                if (event.getEventType() == MouseEvent.MOUSE_DRAGGED) {
                    doMove(event);
                }
        }
    }

    /**
     * Implementacja scrollowania
     */
    static class OkragScrollHandler implements EventHandler<ScrollEvent>{
        Okrag okrag;

        /**
         *  Jesli nacisnelismy na okrag
         */
        private void doScale(ScrollEvent e){
                double x = e.getX();
                double y = e.getY();
                if (okrag.isHit(x, y)) {
                    okrag.addradius(e.getDeltaY() * 0.2);
                }
        }
        @Override
        public void handle(ScrollEvent event) {
                okrag = (Okrag) event.getSource();
                if (event.getEventType() == ScrollEvent.SCROLL) {
                    doScale(event);
                }
        }
    }
}
