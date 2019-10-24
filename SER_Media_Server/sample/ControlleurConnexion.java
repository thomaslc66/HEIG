package sample;

import ch.heigvd.iict.ser.imdb.models.DataForMedia;
import ch.heigvd.iict.ser.rmi.IClientApi;
import ch.heigvd.iict.ser.rmi.IServerApi;
import javafx.scene.control.Button;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class ControlleurConnexion  extends UnicastRemoteObject implements IClientApi {

    /**
     * Membres privés
     */
    private DataForMedia dataForMedia = null;
    private IServerApi remoteConenxion = null;
    private boolean isStillconnected = false;
    private Button refButton;

    /**
     * Constructeur, initialise le membre "refButton" et lance le point d'entrée (init)
     * @param button
     * @throws RemoteException
     */
    ControlleurConnexion(Button button) throws RemoteException {
        super();
        refButton = button;
        init();
    }

    /**
     * Point d'entrée du programme, initialise la connexion au serveur via le port 999
     * @throws RemoteException
     */
    public void init() throws RemoteException{
        try {
            remoteConenxion = (IServerApi) Naming.lookup("//localhost:999/RmiService");
        }catch (Exception e){
            e.printStackTrace();
        }

        if (remoteConenxion.isStillConnected()){
            isStillconnected = true;
            remoteConenxion.addObserver(this);  // PlexMedia s'enregistre en tant qu'observateurs de PlexAdmin
            System.out.println("Enregistré en tant qu'observer de plex admin");
        }else {
            System.out.println("Erreur de connexionToAdmin lors de la récupération du JSON");
        }
    }

    /**
     * @param observable
     * @param signalType
     * @param updateMsg
     * @throws RemoteException
     */
    @Override
    public void update(Object observable, Signal signalType, String updateMsg) throws RemoteException {
        System.out.println("Signal Reçu : " + signalType.name() + " : " + updateMsg);
        System.out.println("Notification reçue");
        refButton.setStyle("-fx-background-color: green");

    }

    /**
     * Simple getter
     * @return
     */
    public boolean getIsStillconnected(){
        return isStillconnected;
    }

    /**
     * @return un objet DataForMedia contenant les projections au format JSON
     */
    public DataForMedia getProjections(){
        try{
            if(remoteConenxion.isStillConnected()){
                dataForMedia = remoteConenxion.getJson();
            }
        }catch(RemoteException e){
            e.printStackTrace();
        }catch(Exception e){
            e.printStackTrace();    //debug purpose
        }

        return dataForMedia;
    }
}

