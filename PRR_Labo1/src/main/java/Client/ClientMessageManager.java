package Client;

import Common.Configuration.Configuration;
import Common.Message.ProtocolMessage.*;
import Common.MessageManager.MessageManager;

import java.io.IOException;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * @File        : ClientMessageManager.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Client Message Manager
 *
 * @Comment(s)  : -
 *
 * @See         : MessageManager
 */
public class ClientMessageManager extends MessageManager {
    private final static Logger LOG = Logger.getLogger(ClientMessageManager.class.getName());

    private ClientUnicast clientUnicast;
    private Client client;
    private boolean hasDoneFirstStep;
    private InetAddress unicastAddress;
    private int unicastPort;
    private byte lastMessageReceivedId;
    private byte lastMessageIdSend;

    public ClientMessageManager(
            Client client,
            InetAddress multicastAddress,
            int multicastPort,
            InetAddress unicastAddress,
            int unicastPort) {

        this.lastMessageReceivedId = 0;
        this.lastMessageIdSend = 0;
        this.client = client;
        this.hasDoneFirstStep = false;
        this.unicastAddress = unicastAddress;
        this.unicastPort = unicastPort;
        try {
            this.clientUnicast = new ClientUnicast(this, new DatagramSocket());
            new ClientMulticast(this, multicastAddress, new MulticastSocket(multicastPort));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Get if the client has done first step
     * @return true -> has done first step else false
     */
    public boolean hasDoneFirstStep() {
        return hasDoneFirstStep;
    }

    @Override
    public void process(MessageSync messageSync) {
        if(Configuration.isDebug()) {
            LOG.info("Sync message received with id : " + messageSync.getId());
        }
        client.snapshotDeltaTime();
        lastMessageReceivedId = messageSync.getId();
    }

    @Override
    public void process(MessageFollowUp messageFollowUp) {
        if(messageFollowUp.getId() == lastMessageReceivedId) {
            if (Configuration.isDebug()) {
                LOG.info("Follow Up message received with id : " + messageFollowUp.getId());
            }
            client.calculateDeltaTime(messageFollowUp.getTime());
            if (!hasDoneFirstStep) {
                hasDoneFirstStep = true;
                sendSynchronisationMessage();
            }
        } else {
            LOG.log(Level.WARNING,
                    "Message id (" + messageFollowUp.getId() +
                            ") do not match with last message id received : " + lastMessageReceivedId);
        }
    }

    @Override
    public void process(MessageDelayRequest messageDelayRequest) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void process(MessageDelayResponse messageDelayResponse) {
        if(messageDelayResponse.getId() == lastMessageIdSend) {
            if (Configuration.isDebug()) {
                LOG.info("Delay Respond message received from server with id : " + messageDelayResponse.getId());
            }
            client.calculateDelayTime(messageDelayResponse.getTime());
            client.setTime();
        } else {
            LOG.log(Level.WARNING,
                    "Message id (" + messageDelayResponse.getId() +
                            ") do not match with last message id sent : " + lastMessageIdSend);
        }
    }

    @Override
    public void sendSynchronisationMessage() {
        byte id = generateID();

        if(Configuration.isDebug()) {
            LOG.info("Send Delay Request with id : " + id);
        }

        client.snapshotDelayTime();
        clientUnicast.sendMessage(new MessageDelayRequest(id, unicastAddress, unicastPort));
        lastMessageIdSend = id;
    }
}
