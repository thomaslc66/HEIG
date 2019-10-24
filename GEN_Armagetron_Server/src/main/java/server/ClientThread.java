/**
 * @project     : Argmagetron
 * @file        : ClientThread.java
 * @author(s)   : Michael Brouchoud
 * @date        : 18.05.2017
 *
 * @brief        : Use as interface between client and controller to receive object from server,
 *                 send object to server and connect to the server
 *
 */
package server;

import share.Util;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

/**
 * @class ClientThread
 */
class ClientThread implements Runnable {
    private Controller controller;
    private Server server;
    private Socket socket;
    private ObjectInputStream sInput;
    private ObjectOutputStream sOutput;
    private boolean isRunning;

    /**
     * Constructor
     *
     * @param server The server
     * @param socket The server's socket
     * @param controller The controller
     */
    ClientThread(Server server, Socket socket, Controller controller) {
        this.isRunning = true;
        this.controller = controller;
        this.socket = socket;
        this.server = server;
    }

    /**
     * @fn void init()
     *
     * @brief Init to receive a connection from client
     *
     * @author Michael Brouchoud
     */
    void init() {
        try {
            sOutput = new ObjectOutputStream(socket.getOutputStream());
            sInput = new ObjectInputStream(socket.getInputStream());

            controller.processData(sInput.readObject(), this);
        } catch (IOException e) {
            Util.print("Error when trying to create input/output stream : " + e);
            e.printStackTrace();
            this.close();
        } catch (ClassNotFoundException e) {
            Util.print("Connection failed, the first message send from client must be a ConnectionData : " + e);
            e.printStackTrace();
            this.close();
        }
        new Thread(this).start();
    }

    /**
     * @fn public void run()
     *
     * @brief Read the object send by client and send it to the controller
     *
     * @author Michael Brouchoud
     */
    public void run() {
        while(isRunning) {
            try {
                controller.processData(sInput.readObject(), this);
            }
            catch (IOException e) {
                Util.print("Connection with client close : " + e.getMessage());
                this.server.remove(this);
                this.close();
            }
            catch(ClassNotFoundException e) {
                Util.print("No know this object " + e);
                e.printStackTrace();
                this.server.remove(this);
                this.close();
            }
        }
        this.server.remove(this);
        this.close();
    }

    /**
     * @fn void close()
     *
     * @brief Close input/output stream and socket
     *
     * @author Michael Brouchoud
     */
    void close() {
        isRunning = false;
        try {
            if(sOutput != null) sOutput.close();
        }
        catch (IOException e) {
            Util.print("Error when client close output stream : " + e);
            e.printStackTrace();
        }

        try {
            if(sInput != null) sInput.close();
        }
        catch (IOException e) {
            Util.print("Error when client close input stream : " + e);
            e.printStackTrace();
        }

        try {
            if(socket != null) socket.close();
        }
        catch (IOException e) {
            Util.print("Error when client close socket : " + e);
            e.printStackTrace();
        }
    }
    /**
     * @fn void sendData(Object o)
     *
     * @brief Send object to client
     *
     * @author Michael Brouchoud
     *
     * @param o The object to send
     */
    void sendData(Object o) {
        if(!socket.isConnected()) {
            Util.print("Client disconnected");
            server.remove(this);
        }

        try {
            sOutput.writeObject(o);
            sOutput.reset(); //To not send the same object
        }
        catch(IOException e) {
            Util.print("Error when trying to send data to client");
            server.remove(this);
        }
    }
}
