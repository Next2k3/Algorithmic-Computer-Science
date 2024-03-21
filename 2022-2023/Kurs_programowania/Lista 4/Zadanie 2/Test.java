import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javafx.scene.text.Font;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Test extends Application{
    private Process process;
    private BufferedReader reader;
    public static void main(String[] args){
        launch(args);
    }
    @Override
    public void start(Stage stage){
        stage.setTitle("Wiersz Trójkąta Pascala");
        stage.setResizable(false);
        Label rowlabel = new Label("Podaj wiersz:");
        rowlabel.setFont(new Font("Arial",16));

        TextField inputFieldrow = new TextField();
        inputFieldrow.setPromptText("numery wierszy");
        inputFieldrow.setFont(new Font("Arial", 16));

        Label elementlabel = new Label("Podaj elementy:");
        elementlabel.setFont(new Font("Arial",16));

        TextField inputFieldelement = new TextField();
        inputFieldelement.setPromptText("numer elementu");
        inputFieldelement.setFont(new Font("Arial",16));

        Button button = new Button("Generuj");
        button.setFont(new Font("Arial",16));

        GridPane grid = new GridPane();
        grid.setPadding(new Insets(10));
        grid.setVgap(10);
        grid.setHgap(10);
        grid.add(rowlabel,0,0);
        grid.add(inputFieldrow,1,0);
        grid.add(elementlabel,0,1);
        grid.add(inputFieldelement,1,1);
        grid.add(button,0,2);

        Scene scene = new Scene(grid,350,125);
        scene.setOnKeyPressed(event->{
            if(event.getCode()== KeyCode.ENTER){
                button.fire();
            }
        });
        stage.setScene(scene);
        stage.setOnCloseRequest(e -> System.exit(0));
        stage.show();

        Stage resultStage = new Stage();
        resultStage.setTitle("Wyniki");

        button.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                try {
                    String wiersz = inputFieldrow.getText();
                    int spaceindex=wiersz.indexOf(" ");
                    if(spaceindex<0){
                        spaceindex=wiersz.length();
                    }
                    String wiersz2 = wiersz.substring(0, spaceindex);
                    String[] elementy = inputFieldelement.getText().split(" ");
                    String command = "./Test "+wiersz2;
                    String line;
                    StringBuilder output = new StringBuilder();

                    for (String element: elementy) {
                        process = Runtime.getRuntime().exec(command+" "+ element);
                        reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                        while ((line = reader.readLine()) != null) {
                            output.append(line).append("\n");
                        }
                    }
                    Label resultLabel1=new Label("Wynik:");
                    resultLabel1.setFont(new Font("Arial",16));

                    Label resultLabel2=new Label(output.toString());
                    resultLabel2.setFont(new Font("Arial",16));

                    GridPane resultgrid = new GridPane();
                    resultgrid.add(resultLabel1,0,0);
                    resultgrid.add(resultLabel2,0,1);
                    resultgrid.setPadding(new Insets(10));

                    Scene resultScene = new Scene(resultgrid);
                    resultStage.setY(stage.getY()+stage.getHeight());
                    resultStage.setX(stage.getX());
                    resultStage.setScene(resultScene);
                    resultStage.show();
                }catch(NumberFormatException | IOException e){
                    e.printStackTrace();
                }


            }
        });


    }
}
