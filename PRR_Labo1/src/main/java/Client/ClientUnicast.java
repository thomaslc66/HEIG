package Client;

import Common.Communicator.Receiver;
import Common.Communicator.Sender;
import Common.Encoder.MessageEncoder;
import Common.Message.Message;
import Common.MessageManager.IMessageProcessor;
import Common.MessageManager.IMessageSender;

import java.net.DatagramSocket;

/**
 * @File        : ClientUnicast.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Generate a unicast environment for client
 *
 * @Comment(s)  : -
 *
 */
public class ClientUnicast implements IMessageSender {
    private Sender sender;

    public ClientUnicast(IMessageProcessor messageProcessor, DatagramSocket socket) {
        this.sender = new Sender(socket);
        new Receiver(socket, messageProcessor);
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
