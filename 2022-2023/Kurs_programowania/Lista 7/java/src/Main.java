import javafx.application.Application;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) {
        // Tworzenie i inicjalizowanie obiektu SceneManager
        SceneManager sceneManager = new SceneManager(primaryStage);
        // Wyświetlanie pierwszej sceny
        sceneManager.showFirstScene();
    }

    public static void main(String[] args) {
        // Uruchamianie aplikacji JavaFX
        launch(args);
    }
}