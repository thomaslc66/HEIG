/**
 * @project     : Argmagetron
 * @file        : Game.java
 * @author(s)   : Michael Brouchoud
 * @date        : 30.05.2017
 *
 * @brief        : Use only for the Tests
 *
 */

package clientTest;

import data.ConnectionData;
import share.Util;

import java.awt.*;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

/**
 * @class Client
 */
public class Client implements Runnable {

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket socket;
    private Thread thread;
    private boolean keepGoing;

    private String serverAddress;
    private int port;

    /**
     * Constructor
     *
     * @param serverAddress The server Adress
     * @param port The server's port
     */
    public Client(String serverAddress, int port){
        this.serverAddress = serverAddress;
        this.port = port;
        this.keepGoing = true;
        this.thread = new Thread(this);
        this.connect();
    }

    /**
     * @fn private void connect()
     *
     * @brief Connect to the server
     *
     * @author Michael Brouchoud
     */
    private void connect(){
        try{
            socket = new Socket(serverAddress, port);
        }catch(Exception e){
            Util.print("Error when trying to connect to server" + e);
            e.printStackTrace();
        }

        Util.print("Connecton accepted on port : " +  port);

        try{
            input = new ObjectInputStream(socket.getInputStream());
            output = new ObjectOutputStream(socket.getOutputStream());
        }catch(IOException e){
            Util.print("Error when trying to create input/output stream :" + e);
            e.printStackTrace();
        }

        this.thread.start();

        //this.sendData(new ConnectionData(this.username, new Color(Util.rand.nextInt(255), Util.rand.nextInt(255), Util.rand.nextInt(255))));
        this.sendData(new ConnectionData("", Color.yellow));
    }

    /**
     * @fn private void sendData(Object o)
     *
     * @brief Send object to the server
     *
     * @author Michael Brouchoud
     *
     * @param o The object to send
     */
    private void sendData(Object o) {
        if(!socket.isConnected()) {
            Util.print("Client disconnected");
            this.close();
        }

        try {
            output.writeObject(o);
            output.reset(); //To not send the same object
        }
        catch(IOException e) {
            Util.print("Exception when trying to send data to server :" + e);
            Util.print(e.toString());
        }
    }

    /**
     * @fn private void close()
     *
     * @brief close the client
     *
     * @author Michael Brouchoud
     */
    private void close(){
        this.keepGoing = false;
        try {
            if(output != null) output.close();
        }
        catch (IOException e) {
            Util.print("Error when trying to close output stream : " + e);
            e.printStackTrace();
        }

        try {
            if(input != null) input.close();
        }
        catch (IOException e) {
            Util.print("Error when trying to close input stream : " + e);
            e.printStackTrace();
        }

        try {
            if(socket != null) socket.close();
        }
        catch (IOException e) {
            Util.print("Error when trying to close socket : " + e);
            e.printStackTrace();
        }
    }

    /**
     * @fn public void run()
     *
     * @brief Listen to receive object from the server
     *
     * @author Michael Brouchoud
     */
    public void run() {
        while (this.keepGoing) {
            try {
                Util.print("Receveid object : " + input.readObject());
            } catch (IOException e) {
                Util.print("Connection with server close : " + e.getMessage());
                this.close();
            } catch (ClassNotFoundException e) {
                Util.print("No known the received data : " + e);
                e.printStackTrace();
            }
        }
    }
}
