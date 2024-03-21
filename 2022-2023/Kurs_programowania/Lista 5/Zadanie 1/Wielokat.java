import javafx.event.EventHandler;
import javafx.scene.control.*;
import javafx.scene.input.MouseButton;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.ScrollEvent;
import javafx.scene.paint.Color;
import javafx.scene.shape.Polygon;
import javafx.scene.layout.*;

import javafx.scene.transform.Rotate;

import java.io.*;

/**
 * Klasa tworzaca wielokat rozszerzajaca Polygon
 */
public class Wielokat extends Polygon implements Serializable{
    /**
     * Główny konstruktor
     * @param points punkty bedace wieszchołkami obiektu
     * @param color kolor obiektu
     */
    public Wielokat(double[] points, Color color){
        super(points);
        setFill(color);
        setOnMouseClicked(new WielokatEventHandler());
        setOnMouseDragged(new WielokatEventHandler());
        setOnScroll(new WielokatScrollHandler());
    }

    /**
     * metoda sprawdzajaca czy zdarzenie dotyczy obiektu
     * @param x wspolrzedna "x" punktu
     * @param y wspolrzedna "y" punktu
     * @return zwraca bool
     */
    public boolean isHit(double x, double y) {

        return getBoundsInLocal().contains(x,y);
    }

    /**
     * Metoda odpowiedzialna za zmiane wpolrzednej x obiektu
     * @param x parametr o który zostanie zmienione wpolrzedna x obiektu
     */
    public void addX(double x) {
        for(int i=0;i<getPoints().size();i+=2) {
            getPoints().set(i, getPoints().get(i)+x);
        }
    }
    /**
     * Metoda odpowiedzialna za zmiane wpolrzednej y obiektu
     * @param y parametr o który zostanie zmienione wpolrzedna y obiektu
     */
    public void addY(double y) {
        for(int i=1;i<getPoints().size();i+=2) {
            getPoints().set(i, getPoints().get(i)+y);
        }
    }

    /**
     * Metoda skalujaca obiekt o 1.2
     */
    public void scaleUp() {
        double centerX = getBoundsInLocal().getCenterX();
        double centerY = getBoundsInLocal().getCenterY();
        for(int i=0;i<getPoints().size();i+=2) {
            double x = getPoints().get(i);
            double y = getPoints().get(i+1);

            double deltaX = x - centerX;
            double deltaY = y - centerY;

            double scaledX = centerX + (deltaX*1.2);
            double scaledY = centerY + (deltaY*1.2);

            getPoints().set(i,scaledX);
            getPoints().set(i+1,scaledY);
        }
    }

    /**
     * Metoda skalujaca obiet o 1/1.2
     */
    public void scaleDown() {
        double centerX = getBoundsInLocal().getCenterX();
        double centerY = getBoundsInLocal().getCenterY();
        for(int i=0;i<getPoints().size();i+=2) {
            double x = getPoints().get(i);
            double y = getPoints().get(i+1);

            double deltaX = x - centerX;
            double deltaY = y - centerY;

            double scaledX = centerX + (deltaX/1.2);
            double scaledY = centerY + (deltaY/1.2);

            getPoints().set(i,scaledX);
            getPoints().set(i+1,scaledY);
        }
    }

    /**
     * Metoda Rotujca obiekt o zadany kąt wzgledem punktu
     * @param angle kat o który zostanie obrócony obiekt
     * @param x wspolrzedna "x" punktu
     * @param y wspolrzedna "y" puntku
     */
    public void doRotate(double angle,double x,double y ){
        getTransforms().add(new Rotate(angle,x,y));
    }

    /**
     * Implementacja przesuwania
     */
    class WielokatEventHandler implements EventHandler<MouseEvent>,Serializable{
        Wielokat wielokat;

        private double x;
        private double y;

        /**
         * Jesli nacisniesz na wielokat
         */
        private void doMove(MouseEvent event) {

            double dx = event.getX() - x;
            double dy = event.getY() - y;

            if (wielokat.isHit(x, y)) {
                wielokat.addX(dx);
                wielokat.addY(dy);
            }
            x += dx;
            y += dy;
        }
        @Override
        public void handle(MouseEvent event){
            wielokat = (Wielokat) event.getSource();
            if(event.getButton()== MouseButton.SECONDARY){
                if(event.getEventType()==MouseEvent.MOUSE_CLICKED ) {
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
                    Label label = new Label("Podaje nazwe pliku:");
                    TextField textField = new TextField();
                    textField.setPromptText("nazwa ");
                    Button button = new Button("Zapisz");

                    gridPane.add(label,0,0);
                    gridPane.add(textField,0,1);
                    gridPane.add(button,0,2);

                    MenuItem zapiszitem = new MenuItem(null,gridPane);

                    pickermenu.getItems().add(pickeritem);
                    rotatemenu.getItems().add(rotateitem);
                    zapiszmenu.getItems().add(zapiszitem);

                    menuedycja.getItems().addAll(pickermenu,rotatemenu,zapiszmenu,usun);
                    menuedycja.show(wielokat,event.getScreenX(),event.getScreenY());

                    button.setOnAction(event2 -> {
                        String nazwa;
                        String objekt;

                        nazwa = textField.getText();
                        nazwa += ".txt";

                        objekt=wielokat.toString();
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
                    usun.setOnAction(event1 -> ((Pane) getParent()).getChildren().remove(wielokat));
                    colorPicker.setOnAction(event1 -> setFill(colorPicker.getValue()));
                    slider.valueProperty().addListener((obs,oldvalue,newvalue)->{
                        double centerx=0;
                        double centery=0;
                        if (getPoints().size() != 0) {
                            for (int i = 0; i < getPoints().size(); i += 2) {
                                centerx += getPoints().get(i);
                                centery += getPoints().get(i + 1);
                            }
                            centerx /= (getPoints().size() / 2.0);
                            centery /= (getPoints().size() / 2.0);
                        }
                        doRotate((double) newvalue-(double)oldvalue,centerx,centery);
                    });
                }
            }else {
                if (event.getEventType() == MouseEvent.MOUSE_CLICKED) {
                    x = getTranslateX() - event.getSceneX();
                    y = getTranslateY() - event.getSceneY();

                }
                if (event.getEventType() == MouseEvent.MOUSE_DRAGGED) {
                    doMove(event);
                }
            }
        }
    }

    /**
     * Implementacja przesuwania
     */
    class WielokatScrollHandler implements EventHandler<ScrollEvent>{

        Wielokat wielokat;

        /**
         * Jesli nacisniesz na wielokat
         */
        private void doScale(ScrollEvent e) {

            double delta = e.getDeltaY();
            if(delta>0){
                scaleUp();
            }else{
                scaleDown();
            }
            e.consume();
        }

        @Override
        public void handle(ScrollEvent event) {

            wielokat = (Wielokat) event.getSource();
            if (event.getEventType()==ScrollEvent.SCROLL){
                doScale(event);
            }
        }
    }

}
