package Server;

import Common.Communicator.Sender;
import Common.Encoder.MessageEncoder;
import Common.Message.Message;
import Common.MessageManager.IMessageSender;

import java.net.MulticastSocket;

/**
 * @File        : ServerMulticast.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Generate a multicast environment for server
 *
 * @Comment(s)  : -
 *
 * @See         : IMessageSender
 */
public class ServerMulticast implements IMessageSender {
    private Sender sender;

    public ServerMulticast(MulticastSocket socket) {
        this.sender = new Sender(socket);
    }

    @Override
    public void sendMessage(Message message) {
        sender.send(
                MessageEncoder.encode(message),
                message.getReceivedPacketAddress(),
                message.getReceivedPacketPort()
        );
    }
}
