package Client;

import Common.Communicator.MulticastReceiver;
import Common.MessageManager.IMessageProcessor;

import java.net.InetAddress;
import java.net.MulticastSocket;

/**
 * @File        : ClientMulticast.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Generate a multicast environment for client
 *
 * @Comment(s)  : -
 *
 */
public class ClientMulticast {
    public ClientMulticast(IMessageProcessor messageProcessor, InetAddress multicastAddress, MulticastSocket socket) {
        new MulticastReceiver(socket, messageProcessor, multicastAddress);
    }
}
