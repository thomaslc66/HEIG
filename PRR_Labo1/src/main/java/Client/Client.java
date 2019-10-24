package Client;

import Common.Configuration.Configuration;

import java.io.IOException;
import java.net.*;
import java.util.Random;
import java.util.logging.Logger;

/**
 * @File        : Client.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Launch Client
 *
 * @Comment(s)  : -
 */
public class Client {
    private  final static Logger LOG = Logger.getLogger(Client.class.getName());

    private ClientMessageManager messageManager;
    private long deltaTimeSnapshotTime;
    private long delayTimeSnapshotTime;
    private long deltaTime;
    private long delayTime;
    private Random r;

    private Client() {

        r = new Random();

        try{
            messageManager = new ClientMessageManager(
                    this,
                    InetAddress.getByName(Configuration.getMulticastAddress()),
                    Configuration.getMulticastPort(),
                    InetAddress.getByName(Configuration.getUnicastAddress()),
                    Configuration.getUnicastPort()
            );
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Send request message every [4K;60K] after received one time a sync and followup message
        new Thread(new Runnable() {
            int period;
            int high = Configuration.getSleepTime() * 60;
            int low = Configuration.getSleepTime() * 4;

            @Override
            public void run() {
                while(true) {
                    if (messageManager.hasDoneFirstStep()) {
                        messageManager.sendSynchronisationMessage();
                    }
                    try {
                        period = r.nextInt(high - low) + low;
                        Thread.currentThread().sleep(period);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
    }

    public static void main(String[] args) {
        new Client();
    }

    /**
     * Set the client time
     */
    public void setTime() {
        long systemTime = System.currentTimeMillis();
        long time = systemTime + delayTime + deltaTime;
        LOG.info("LocalTime : " + systemTime);
        LOG.info("Server time : " + time);
    }

    /**
     * Take a snapshot of the delta time
     */
    public void snapshotDeltaTime() {
        this.deltaTimeSnapshotTime = System.currentTimeMillis();
    }

    /**
     * Calculate delta time
     * @param masterTime The master time
     */
    public void calculateDeltaTime(long masterTime) {
        deltaTime = masterTime - deltaTimeSnapshotTime;
    }

    /**
     * Take a snapshot of the delay time
     */
    public void snapshotDelayTime() {
        this.delayTimeSnapshotTime = System.currentTimeMillis();
    }

    /**
     * Calculate delay time
     * @param masterTime The master time
     */
    public void calculateDelayTime(long masterTime) {
        delayTime = (masterTime - delayTimeSnapshotTime) / (long)2;
    }
}
