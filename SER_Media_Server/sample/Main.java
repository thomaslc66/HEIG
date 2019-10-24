package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {

    /**
     * Lancement de l'interface graphique
     * @param primaryStage
     * @throws Exception
     */
    @Override
    public void start(Stage primaryStage) throws Exception{
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/sample/sample.fxml"));
        primaryStage.setTitle("Plex Media");
        Parent racine = loader.load();
        Scene sc = new Scene(racine);
        primaryStage.setScene(sc);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
