package Server;

import Common.Configuration.Configuration;
import Common.MessageManager.MessageManager;

import java.io.IOException;
import java.net.InetAddress;
import java.util.Timer;
import java.util.TimerTask;

/**
 * @File        : Server.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Launch Server
 *
 * @Comment(s)  : -
 */
public class Server {
    private MessageManager messageManager;

    private Server() {
        try{
            messageManager = new ServerMessageManager(
                    InetAddress.getByName(Configuration.getMulticastAddress()),
                    Configuration.getMulticastPort(),
                    Configuration.getMulticastServerPort(),
                    Configuration.getUnicastPort()
            );
        }
        catch (IOException e) {
            e.printStackTrace();
        }

        // Send every K second a sync message
        new Timer().schedule(new TimerTask() {
            @Override
            public void run() {
                messageManager.sendSynchronisationMessage();
            }
        }, 0, Configuration.getSleepTime());
    }

    public static void main(String[] args) {
        new Server();
    }
}
