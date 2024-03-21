import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Rectangle2D;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import javafx.stage.Screen;
import javafx.scene.input.KeyCode;

public class Test extends Application {
    public static void main(String[] args){
        launch(args);
    }
    @Override
    public void start(Stage stage){
        stage.setTitle("Trojkąt Pascala");

        Screen screen = Screen.getPrimary();
        Rectangle2D bounds = screen.getVisualBounds();

        double maxWidth = bounds.getWidth()-40;

        stage.setY(0);
        stage.setX(maxWidth/2-550/2);

        Label label = new Label("Podaj rozmiar trójkąta Pascala:");
        label.setFont(new Font("Arial", 16));

        TextField inputField = new TextField();
        inputField.setPromptText("Rozmiar trójkąta");
        inputField.setFont(Font.font("Arial", 16));

        Button button = new Button("Generuj");
        button.setFont(Font.font("Arial", 16));

        Label resultText = new Label();
        resultText.setFont(Font.font("Arial", 16));

        Stage secondeStage =new Stage();
        secondeStage.setTitle("Obraz Trójkąt Pascala");

        button.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                try{
                    int size =Integer.parseInt(inputField.getText());
                    if(size<1){
                        resultText.setText("Invalid input: size<1");
                    }
                    else resultText.setText(TrojkatPascala.TrojkatPascala(size));
                }catch(NumberFormatException e){
                    resultText.setText("Invalid input: "+ e.getMessage());
                }

                ScrollPane scrollPane = new ScrollPane(resultText);
                scrollPane.setPadding(new Insets(10));

                VBox vbox= new VBox(scrollPane);

                Screen screen = Screen.getPrimary();
                Rectangle2D bounds = screen.getVisualBounds();

                secondeStage.setY(stage.getY()+stage.getHeight());
                secondeStage.setX(0);

                double textWidth = resultText.prefWidth(-1);
                double textHeight = resultText.prefHeight(-1);

                double maxWidth = bounds.getWidth()-40;
                double maxHeight = bounds.getHeight()-40-stage.getY()-stage.getHeight();
                double newWidth = Math.min(textWidth+20,maxWidth);
                double newHeight = Math.min(textHeight+20,maxHeight);

                Scene scene = new Scene(vbox,newWidth,newHeight);
                secondeStage.setScene(scene);
                secondeStage.show();
            }
        });
        secondeStage.close();

        GridPane grid = new GridPane();
        grid.add(label, 0, 0);
        grid.add(inputField, 1, 0);
        grid.add(button, 2, 0);
        grid.add(resultText, 0, 1, 3, 1);


        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new Insets(10, 10, 10, 10));

        Scene scene = new Scene(grid, 550, 50);
        scene.setOnKeyPressed(event ->{
            if(event.getCode()==KeyCode.ENTER){
                button.fire();
            }
        });
        stage.setScene(scene);

        stage.setOnCloseRequest(e -> System.exit(0));
        stage.show();
    }
}
