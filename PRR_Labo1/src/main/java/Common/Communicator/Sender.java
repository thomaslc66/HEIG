package Common.Communicator;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

/**
 * @File        : Sender.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Basic Structure to send packets
 *
 * @Comment(s)  : -
 *
 * @See         : Communicator
 */
public class Sender extends Communicator {
    public Sender(DatagramSocket socket) {
        super(socket);
    }

    public void send(byte[] message, InetAddress address, int port) {
        try {
            getSocket().send(new DatagramPacket(message, message.length, address, port));
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}
