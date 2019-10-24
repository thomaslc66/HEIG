/**
 * @project     : Argmagetron
 * @file        : Server.java
 * @author(s)   : Michael Brouchoud
 * @date        : 18.05.2017
 *
 * @brief        : Server
 *
 */
package server;

import share.Util;

import java.io.*;
import java.net.*;
import java.util.*;

/**
 * @class Server
 */
public class Server implements Runnable {
    private ArrayList<ClientThread> clientsThread;
    private ServerSocket serverSocket;
    private boolean keepGoing;
    private Controller controller;

    /**
     * Constructor
     *
     * @param port The server's port
     */
    Server(short port) {
        this.controller = new Controller(this);
        this.clientsThread = new ArrayList<ClientThread>();
        this.keepGoing = true;
        try {
            this.serverSocket = new ServerSocket(port);
            Util.print("server is waiting connection on port : " + port);
        }
        catch (IOException e) {
            Util.print("Error when trying the create ServerSocket : " + e);
            e.printStackTrace();
        }

        new Thread(this).start();
    }

    /**
     * @fn private void close()
     *
     * @brief Close connection with client
     *
     * @author Michael Brouchoud
     */
    private void close() {
        keepGoing = false;

        for(ClientThread clientThread : clientsThread) {
            clientThread.close();
        }

        try {
            serverSocket.close();
        }
        catch(IOException e) {
            Util.print("Error when server close socket : " + e);
            e.printStackTrace();
        }
    }

    /**
     * @fn void broadcastClients(Object o)
     *
     * @brief Broadcast object to all clients
     *
     * @author Michael Brouchoud
     *
     * @param o
     */
    void broadcastClients(Object o) {
        synchronized (o) {
            for (ClientThread clientThread : clientsThread) {
                clientThread.sendData(o);
            }
        }
    }

    /**
     * @fn synchronized void remove(ClientThread clientThread)
     *
     * @brief Remove client from client's list
     *
     * @author Michael Brouchoud
     *
     * @param clientThread
     */
    synchronized void remove(ClientThread clientThread) {
        clientsThread.remove(clientThread);
    }

    /**
     * @fn public void run()
     *
     * @brief Server is waiting for new client connection
     *
     * @author Michael Brouchoud
     */
    public void run() {
        keepGoing = true;

        while(keepGoing)
        {
            try {
                ClientThread clientThread = new ClientThread(this, serverSocket.accept(), controller);
                clientsThread.add(clientThread);
                clientThread.init();
            }
            catch (IOException e) {
                Util.print("Error while client trying to connect : " + e);
                e.printStackTrace();
            }
        }

        this.close();
    }

    /**
     * @fn ClientThread getClientThread(int index)
     *
     * @brief Get a clientThread corresponding to the index
     *
     * @author Michael Brouchoud
     *
     * @param index The index
     * @return The clientThread corresponding to index
     */
    ClientThread getClientThread(int index) {
        return this.clientsThread.get(index);
    }

    /**
     * @fn void setController(Controller controller)
     *
     * @brief Set the Controller
     *
     * @author Michael Brouchoud
     *
     * @param controller The controller
     */
    void setController(Controller controller) {
        this.controller = controller;
    }
}


