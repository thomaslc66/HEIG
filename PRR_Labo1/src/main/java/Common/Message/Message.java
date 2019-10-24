package Common.Message;

import java.net.InetAddress;

/**
 * @File        : MessageDelayRequest.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Define message
 *
 * @Comment(s)  : -
 */
public abstract class Message {
    public static int MESSAGE_SIZE = Byte.SIZE + Byte.SIZE + Long.SIZE;

    private byte type;
    private byte id;
    private long time;
    private InetAddress receivedPacketAddress;
    private int receivedPacketPort;

    protected Message(byte type, byte id, long time, InetAddress receivedPacketAddress, int receivedPacketPort) {
        this(type, id, time);
        this.receivedPacketAddress = receivedPacketAddress;
        this.receivedPacketPort = receivedPacketPort;
    }

    protected Message(byte type, byte id, long time) {
        this.type = type;
        this.id = id;
        this.time = time;
    }

    /**
     * Get message size
     * @return Message size
     */
    public int getSize() {
        return MESSAGE_SIZE;
    }

    /**
     * Get message type
     * @return Message type
     */
    public byte getType() {
        return type;
    }


    /**
     * Get message id
     * @return Message id
     */
    public byte getId() {
        return id;
    }

    /**
     * Get message time
     * @return Message time
     */
    public long getTime() {
        return time;
    }

    /**
     * Get message receive address packet
     * @return Message receive address packet
     */
    public InetAddress getReceivedPacketAddress() {
        return receivedPacketAddress;
    }

    /**
     * Get message receive port packet
     * @return Message receive port packet
     */
    public int getReceivedPacketPort() {
        return receivedPacketPort;
    }
}
