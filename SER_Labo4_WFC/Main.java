package ch.heigvd.iict.ser.imdb;

import java.io.IOException;
import java.io.Serializable;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.RMIServerSocketFactory;
import java.rmi.server.UnicastRemoteObject;
import java.util.Observable;
import java.util.Observer;
import java.util.Scanner;

import ch.heigvd.iict.ser.imdb.db.MySQLAccess;
import ch.heigvd.iict.ser.imdb.models.Data;
import ch.heigvd.iict.ser.imdb.models.DataForMedia;
import ch.heigvd.iict.ser.rmi.IClientApi;
import ch.heigvd.iict.ser.rmi.IServerApi;
import com.sun.org.apache.regexp.internal.RE;

public class Main extends Observable implements IServerApi {

	static {
		// this will load the MySQL driver, each DB has its own driver
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			System.err.println("MySQL drivers not found !");
			System.exit(1);
		}

		//database configuration
		MySQLAccess.MYSQL_URL 		= "docr.iict.ch";
		MySQLAccess.MYSQL_DBNAME 	= "imdb";
		MySQLAccess.MYSQL_USER 		= "imdb";
		MySQLAccess.MYSQL_PASSWORD 	= "imdb";
	}

	private static Scanner scanner = new Scanner(System.in);
	private Data lastData = null;

	public static void main(String[] args) {
		Main rmiServer = new Main();

		try {
			Registry rmiRegistry = LocateRegistry.createRegistry(9999);
			IServerApi rmiService = (IServerApi) UnicastRemoteObject.exportObject(rmiServer, 9999);
			rmiRegistry.bind("RmiService", rmiService);
		} catch (Exception ex) {
			ex.printStackTrace();
		}

		rmiServer.run();
	}


	public void addObserver(IClientApi client) throws RemoteException {
		WrappedObserver wo = new WrappedObserver(client);
		addObserver(wo);
		System.out.println("Added observer: " + client);
	}

	public boolean isStillConnected() throws RemoteException {
		return true;
	}

	public Data getData() throws RemoteException{
		return this.lastData;
	}

	public DataForMedia getJson() throws RemoteException {
		return null;
	}

	private void run() {
		System.out.println("Serveur RMI démarré");
		boolean continuer = true;		
		while(continuer) {
			System.out.print("Select the data version to download [1/2/3/0=quit]: ");
			int choice = -1;
			try {
				choice = scanner.nextInt();
			} catch(Exception e) {
				e.printStackTrace();
			}

			if(choice == 0) continuer = false;
			else if(choice >= 1 && choice <= 3) {
				Worker worker = new Worker(choice);
				this.lastData = worker.run();


				if(lastData != null){
					try {
						setChanged();
						notifyObservers(getData());
						System.out.println("observateur notifié");
					}catch (RemoteException e){
						System.out.println("Erreur d'exécution dans la notification des observateur : " + e);
					}
				}
				//TODO notify client
				/***
				 * 		• Notifier l’observateur(plexAdmin)
				 		• Rajouter une méthode « getData » qui retournera la structure de données
				 		lastData, sur demande de l’observateur.
 				 */
			}
		}
	}

	private class WrappedObserver implements Observer, Serializable {

		private static final long serialVersionUID = -2067345842536415833L;

		private IClientApi ro = null;

		public WrappedObserver(IClientApi ro) {
			this.ro = ro;
		}

		public void update(Observable o, Object arg) {
			try {
				ro.update(o.toString(), IClientApi.Signal.UPDATE_REQUESTED, arg.toString());
			} catch (RemoteException e) {
				System.out.println("Remote exception removing observer: " + this);
				o.deleteObserver(this);
			}
		}
	}

}
