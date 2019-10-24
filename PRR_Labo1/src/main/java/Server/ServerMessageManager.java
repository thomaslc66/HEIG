package Server;

import Common.Configuration.Configuration;
import Common.Message.ProtocolMessage.MessageDelayRequest;
import Common.Message.ProtocolMessage.MessageDelayResponse;
import Common.Message.ProtocolMessage.MessageFollowUp;
import Common.Message.ProtocolMessage.MessageSync;
import Common.MessageManager.MessageManager;

import java.io.IOException;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.util.logging.Logger;

/**
 * @File        : ServerMessageManager.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Server Message Manager
 *
 * @Comment(s)  : -
 *
 * @See         : MessageManager
 */
public class ServerMessageManager extends MessageManager {
    private final static Logger LOG = Logger.getLogger(ServerMessageManager.class.getName());

    private ServerMulticast serverMulticast;
    private ServerUnicast serverUnicast;
    private InetAddress multicastAddress;
    private int multicastPort;

    public ServerMessageManager(
            InetAddress multicastAddress,
            int multicastPort,
            int multicastServerPort,
            int unicastPort) {

        this.multicastAddress = multicastAddress;
        this.multicastPort = multicastPort;
        try {
            this.serverUnicast = new ServerUnicast(this, new DatagramSocket(unicastPort));
            this.serverMulticast = new ServerMulticast(new MulticastSocket(multicastServerPort));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void process(MessageSync messageSync) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void process(MessageFollowUp messageFollowUp) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void process(MessageDelayRequest messageDelayRequest) {
        if(Configuration.isDebug()) {
            LOG.info("Request message from client received with id : " + messageDelayRequest.getId());
        }
        long time = System.currentTimeMillis();
        LOG.info("Server time : " + time);
        serverUnicast.sendMessage(new MessageDelayResponse(
                messageDelayRequest.getId(),
                time,
                messageDelayRequest.getReceivedPacketAddress(),
                messageDelayRequest.getReceivedPacketPort()));
    }

    @Override
    public void process(MessageDelayResponse messageDelayResponse) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void sendSynchronisationMessage() {
        byte id = generateID();
        if(Configuration.isDebug()) {
            LOG.info("Send Sync Message to clients with id : " + id);
        }

        serverMulticast.sendMessage(new MessageSync(id, multicastAddress, multicastPort));

        if(Configuration.isDebug()) {
            LOG.info("Send Follow Up Message to clients with id : " + id);
        }

        serverMulticast.sendMessage(
                new MessageFollowUp(id, System.currentTimeMillis() ,multicastAddress, multicastPort)
        );
    }
}
