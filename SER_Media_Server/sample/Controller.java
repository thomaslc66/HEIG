package sample;

import ch.heigvd.iict.ser.imdb.models.DataForMedia;
import com.google.gson.*;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.text.Text;
import java.rmi.RemoteException;

public class Controller {

    /**
     * Membres privés
     */
    ControlleurConnexion connexionToAdmin = null;
    private boolean isStillconnected = false;

    // Objets pour l'interface
    public Label connexionStatus;
    public Label jsonDiplay;
    public Button verifConnexion;
    public Button mediaRecup;
    public TreeView treeView;
    public ScrollPane scrollPane;

    /**
     * initialisation de la connexionToAdmin apres création de la fenêtre
     */
    @FXML
    public void initialize(){
        init();
        mediaRecup.setStyle("-fx-background-color: red");   // Le rouge indique que la connexion n'est pas encore active
    }

    /**
     * Récupération des données depuis Plex Admin via l'objet "connexionToAdmin" auquel on envoie le message
     * getProjections()
     * @param actionEvent
     * @throws RemoteException
     */
    public void getProjectionsFromPlexAdmin(ActionEvent actionEvent) throws RemoteException {
        DataForMedia d = connexionToAdmin.getProjections();
        String jsonData = d.getJsonData();
        JsonObject obj = new JsonParser().parse(jsonData).getAsJsonObject();
        String str = "Récupération des données:\n";

        // Affichage des données dans au format Json
        Gson gson = new GsonBuilder().setPrettyPrinting().create();
        String json = gson.toJson(obj);
        str+= json;

        // Utilisation d'une vue en arbre via TreeView
        Text text = new Text(str);
        scrollPane.setContent(text);
        createTreeView(obj);
    }

    /**
     * Regroupe les éléments à la racine "PlexMedia" de l'arbre
     * @param obj
     */
    public void createTreeView(JsonObject obj){
        TreeItem<String> root = new TreeItem<>("PlexMedia");
        treeView.setRoot(root);

        makeBranch("formatDate: " + obj.get("formatDate").toString(), root);
        makeBranch("formatHeure: " + obj.get("formatHeure").toString(), root);
        projectionBranches(obj.get("projections").getAsJsonArray(), root);
    }

    /**
     * Ajoute les projections à l'arbre TreeView
     * @param projections
     * @param parent
     * @return
     */
    private TreeItem<String> projectionBranches(JsonArray projections, TreeItem<String> parent) {
        TreeItem<String> proj = new TreeItem<>("projections");

        TreeItem<String> film = null;
        for (int i = 0; i < projections.size(); i++){
            film = new TreeItem<>("projection N°: " + i);
            makeBranch("Salle: " + projections.get(i).getAsJsonObject().get("salle").toString(), film);
            makeBranch("Date: " + projections.get(i).getAsJsonObject().get("date").toString(), film);
            makeBranch("Heure: " + projections.get(i).getAsJsonObject().get("heure").toString(), film);
            makeFilm(projections.get(i).getAsJsonObject().get("film").getAsJsonObject(), film);
            proj.getChildren().addAll(film);
        }

        parent.getChildren().add(proj);
        return proj;
    }

    /**
     * Ajoute le film lié à la projection, puis ajoute le tout à l'arbre
     * @param obj
     * @param parent
     * @return
     */
    public TreeItem<String> makeFilm(JsonObject obj, TreeItem<String> parent){
        TreeItem<String> item = new TreeItem<>("Film: " + obj.getAsJsonObject().get("titre").toString());
        item.setExpanded(false);

        makeBranch("Duree: " + obj.get("duree").toString(),item);
        makeActeurs(obj.get("acteurs").getAsJsonArray(), item);

        parent.getChildren().add(item);

        return item;
    }

    /**
     * Ajoute les acteurs au film concerné, puis ajoute le tout à l'arbre
     * @param array
     * @param parent
     * @return
     */
    public TreeItem<String> makeActeurs(JsonArray array, TreeItem<String> parent){
        TreeItem<String> item = new TreeItem<>("Liste des acteurs:");
        item.setExpanded(false);

        TreeItem<String> acteurs = null;
        for (int i = 0; i < array.size(); i++){
            acteurs = new TreeItem<>("Acteur n° " + i);
            makeBranch("nom: " + array.get(i).getAsJsonObject().get("nom").toString(), acteurs);
            makeBranch("naissance: " + array.get(i).getAsJsonObject().get("dateNaissance").toString(), acteurs);
            makeBranch("role: " + array.get(i).getAsJsonObject().get("role").getAsJsonObject().get("personnage").toString(), acteurs);
            item.getChildren().add(acteurs);
        }

        parent.getChildren().add(item);

        return item;
    }

    /**
     * Génère une branche pour l'arbre TreeView
     * @param title
     * @param parent
     * @return
     */
    public TreeItem<String> makeBranch(String title, TreeItem<String> parent){
        TreeItem<String> item = new TreeItem<>(title);
        item.setExpanded(false);
        parent.getChildren().add(item);

        return item;
    }

    /**
     * Contrôle la connexion au serveur PlexAdmin
     * @param actionEvent
     */
    public void checkConnexionToPlexAdmin(ActionEvent actionEvent) {
        if(isStillconnected){
            connexionStatus.setText("Connexion à Plex Admin établie");
        }else{
            connexionStatus.setText("Connexion interompue vers Plex Admin");
            // TODO ajouter un bouton pour relancer la connexionToAdmin
        }
    }

    /**
     * Appel le contrôleur de connexion
     */
    public void init(){
        try {
            connexionToAdmin = new ControlleurConnexion(mediaRecup);
        }catch (RemoteException e){
            connexionStatus.setText("Erreur lors de la connexionToAdmin au serveur Plex Admin");
        }

        if (connexionToAdmin.getIsStillconnected()){
            isStillconnected = true;
            connexionStatus.setText("Connecté avec succès au serveur Plex Admin");
        }
    }
}



