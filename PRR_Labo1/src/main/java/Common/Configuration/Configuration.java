package Common.Configuration;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

/**
 * @File        : Configuration.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Get App Configurations
 *
 * @Comment(s)  : -
 */
public class Configuration {
    private static Configuration configuration;
    private static String multicastAddress;
    private static int multicastPort;
    private static int multicastServerPort;
    private static String unicastAddress;
    private static int unicastPort;
    private static byte messageSyncType;
    private static byte messageFollowUpType;
    private static byte messageDelayRequestType;
    private static byte messageDelayResponseType;
    private static int sleepTime;
    private static boolean debug;

    private Configuration() {
        try {
            InputStream in = getClass().getResourceAsStream("/config.properties");
            Properties properties = new Properties();
            properties.load(in);
            multicastAddress = properties.getProperty("multicastAddress");
            multicastPort = Integer.parseInt(properties.getProperty("multicastPort"));
            multicastServerPort = Integer.parseInt(properties.getProperty("multicastServerPort"));
            unicastAddress = properties.getProperty("unicastAddress");
            unicastPort = Integer.parseInt(properties.getProperty("unicastPort"));
            messageSyncType = Byte.parseByte(properties.getProperty("messageSyncType"));
            messageFollowUpType = Byte.parseByte(properties.getProperty("messageFollowUpType"));
            messageDelayRequestType = Byte.parseByte(properties.getProperty("messageDelayRequestType"));
            messageDelayResponseType = Byte.parseByte(properties.getProperty("messageDelayResponseType"));
            sleepTime = Integer.parseInt(properties.getProperty("sleepTime"));
            debug = Boolean.parseBoolean(properties.getProperty("debug"));
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Get a single instance of Configuration
     * @return A single instance of Configuration
     */
    private static Configuration getInstance() {
        if(configuration == null) {
            synchronized (Configuration.class) {
                if(configuration == null) {
                    configuration = new Configuration();
                }
            }
        }
        return configuration;
    }

    /**
     * Get the server multicast ip address
     * @return The server multicast ip address
     */
    public static String getMulticastAddress() {
        return getInstance().multicastAddress;
    }

    /**
     * Get the common unicastPort to listen
     * @return The common multicastAddress to listen
     */
    public static int getMulticastPort() {
        return getInstance().multicastPort;
    }

    /**
     * Get the multicast Server Port
     * @return The multicast Server Port
     */
    public static int getMulticastServerPort() {
        return getInstance().multicastServerPort;
    }


    /**
     * Get the unicast address
     * @return The unicast address
     */
    public static String getUnicastAddress() {
        return getInstance().unicastAddress;
    }

    /**
     * Get the common to send
     * @return The common to send
     */
    public static int getUnicastPort() {
        return getInstance().unicastPort;
    }

    /**
     * Get the common sync message byte
     * @return The common sync message byte
     */
    public static byte getMessageSyncType() {
        return getInstance().messageSyncType;
    }

    /**
     * Get the common to follow Up byte
     * @return The common follow Up byte
     */
    public static byte getMessageFollowUpType() {
        return getInstance().messageFollowUpType;
    }

    /**
     * Get the common to delay request byte
     * @return The common delay request byte
     */
    public static byte getMessageDelayRequestType() {
        return getInstance().messageDelayRequestType;
    }

    /**
     * Get the common to delay respond byte
     * @return The common delay respond byte
     */
    public static byte getMessageDelayResponseType() {
        return getInstance().messageDelayResponseType;
    }

    /**
     * Get the sleep time K
     * @return The sleep time K
     */
    public static int getSleepTime() {
        return getInstance().sleepTime;
    }

    /**
     * Use to check if in debug mode
     * @return true -> debug mode else normal mode
     */
    public static boolean isDebug() {
        return getInstance().debug;
    }
}

