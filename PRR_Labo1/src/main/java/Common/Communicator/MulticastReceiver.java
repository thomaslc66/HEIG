package Common.Communicator;

import Common.MessageManager.IMessageProcessor;

import java.io.IOException;
import java.net.InetAddress;
import java.net.MulticastSocket;

/**
 * @File        : Communicator.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Basic structure create multicast Receiver
 *
 * @Comment(s)  : -
 *
 */
public class MulticastReceiver extends Receiver {
    private InetAddress multicastAddress;
    private MulticastSocket socket;

    public MulticastReceiver(MulticastSocket socket, IMessageProcessor messageProcessor, InetAddress multicastAddress) {
        super(socket, messageProcessor);
        this.socket = socket;
        this.multicastAddress = multicastAddress;

        // Need to join a group to receive packet with multicast
        try {
            socket.joinGroup(multicastAddress);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Leave the group before to close socket
     */
    @Override
    protected void close() {
        super.close();
        try {
            socket.leaveGroup(multicastAddress);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
