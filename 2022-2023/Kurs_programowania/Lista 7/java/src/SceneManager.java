import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class SceneManager {

    private final Stage primaryStage;
    private final TextField textField = new TextField();
    private Label drawingArea = new Label();
    private PrintWriter output;
    private BufferedReader input;

    public SceneManager(Stage primaryStage) {
        this.primaryStage = primaryStage;
        this.primaryStage.setTitle("Drzewa binarne");
    }

    public void showFirstScene() {
        // Tworzenie etykiety na pierwszej scenie
        Label label = new Label("Wybierz typ danych w drzewie binarnym:");

        // Tworzenie przycisków na pierwszej scenie
        Button button1 = new Button("Integer");
        button1.setOnAction(e -> openSecondScene("Integer"));

        Button button2 = new Button("Double");
        button2.setOnAction(e -> openSecondScene("Double"));

        Button button3 = new Button("String");
        button3.setOnAction(e -> openSecondScene("String"));

        // Ustawienie szerokości przycisków
        button1.setMaxWidth(Double.MAX_VALUE);
        button2.setMaxWidth(Double.MAX_VALUE);
        button3.setMaxWidth(Double.MAX_VALUE);

        // Układanie przycisków w kontenerze VBox
        VBox buttonLayout = new VBox(5);
        buttonLayout.setAlignment(Pos.CENTER);
        buttonLayout.setPadding(new Insets(10));
        buttonLayout.getChildren().addAll(button1, button2, button3);

        // Układanie komponentów na pierwszej scenie
        VBox layout1 = new VBox(10);
        layout1.setAlignment(Pos.CENTER);
        layout1.setPadding(new Insets(10));
        layout1.getChildren().addAll(label, buttonLayout);

        Scene scene1 = new Scene(layout1, 250, 200);

        primaryStage.setScene(scene1);
        primaryStage.show();
    }

    private void openSecondScene(String dataType) {
        try {
            Socket socket = new Socket("localhost", 4444); //The socket is closed by the server

            //For sending data to the server
            PrintWriter output = new PrintWriter(socket.getOutputStream(), true);
            this.output = output;

            //For receiving data from the server
            this.input = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            output.println(dataType);
        } catch (final UnknownHostException e) {
            System.out.println("Server not found: " + e.getMessage());
            System.exit(0);
        } catch (final IOException ex) {
            System.out.println("I/O error: " + ex.getMessage());
            System.exit(0);
        }

        // Tworzenie etykiety na drugiej scenie
        Label label = new Label("Wybrany typ danych w drzewie binarnym: " + dataType);

        textField.setAlignment(Pos.CENTER);
        textField.setPadding(new Insets(10));

        // Tworzenie przycisku powrotu na drugiej scenie
        Button insert = new Button("Dodaj");
        Button delete = new Button("Usuń");
        Button draw = new Button("Wyświetl");
        Button search = new Button("Wyszukaj");
        Button backButton = new Button("Powrót");

        insert.setOnAction(e -> {
            String userInput = textField.getText();
            if (checkArguments(userInput)) {
                output.println("insert");
                output.println(userInput);

                drawingArea.setText(getAnswerFromServer());
            }
            textField.clear();
        });
        delete.setOnAction(e -> {
            String userInput = textField.getText();
            if (checkArguments(userInput)) {
                output.println("delete");
                output.println(userInput);

                drawingArea.setText(getAnswerFromServer());
            }
            textField.clear();
        });
        search.setOnAction(e -> {
            String userInput = textField.getText();
            if (checkArguments(userInput)) {
                output.println("search");
                output.println(userInput);
                String answer = getAnswerFromServer();

                if (answer.equals("true"))
                    showAlert(userInput + " IS in the tree!", AlertType.INFORMATION);
                else if (answer.equals("false"))
                    showAlert(userInput + " IS NOT in the tree!", AlertType.INFORMATION);
            }
            textField.clear();
        });
        draw.setOnAction(e -> {
            output.println("print");
            drawingArea.setText(getAnswerFromServer());
            textField.clear();
        });

        backButton.setOnAction(e -> {
            showFirstScene();
            drawingArea.setText("");
        });

        // Układ przycisków na drugiej scenie
        HBox buttonLayout = new HBox(10);
        buttonLayout.setAlignment(Pos.CENTER);
        buttonLayout.setPadding(new Insets(10));
        buttonLayout.getChildren().addAll(insert, delete, draw, search, backButton);

        // Układanie komponentów na drugiej scenie
        VBox layout2 = new VBox(10);
        layout2.setAlignment(Pos.CENTER);
        layout2.setPadding(new Insets(10));
        layout2.getChildren().addAll(label, textField, buttonLayout, drawingArea);

        Scene scene2 = new Scene(layout2);

        primaryStage.setScene(scene2);
    }

    private String getAnswerFromServer() {
        try {
            String answer = input.readLine();
            if (answer.equals("wrong_type")) {
                showAlert("Wrong data type!", AlertType.WARNING);
                return "";
            }

            return answer;
        } catch (final IOException ex) {
            System.out.println("I/O error while getting answer from server");
            System.exit(0);
            return "I/O ERROR";
        }
    }

    private boolean checkArguments(String userInput) {
        drawingArea.setText(null);

        if (userInput.split(" ").length != 1) {
            showAlert("Expected 1 argument!", AlertType.WARNING);
            return false;
        }

        return true;
    }

    private void showAlert(String content, AlertType type) {
        Alert infoAlert = new Alert(type);
        infoAlert.setContentText(content);
        infoAlert.showAndWait();
    }
}
