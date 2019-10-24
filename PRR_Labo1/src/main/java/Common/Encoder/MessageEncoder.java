package Common.Encoder;

import Common.Configuration.Configuration;
import Common.Message.Message;
import Common.Message.ProtocolMessage.*;
import Common.MessageManager.IMessageProcessor;

import java.net.DatagramPacket;
import java.nio.ByteBuffer;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * @File        : MessageEncoder.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Tools to encode/decode Message
 *
 * @Comment(s)  : -
 */
public class MessageEncoder {
    private  final static Logger LOG = Logger.getLogger(MessageEncoder.class.getName());

    /**
     * Encode message
     * @param message The message to encode
     * @return A byte array of message
     */
    public static byte[] encode(Message message) {
        return ByteBuffer.allocate(message.getSize())
                .put(message.getType())
                .put(message.getId())
                .putLong(message.getTime()).array();
    }

    /**
     * Decode message
     * @param messageProcessor The processor which will process the message
     * @param packet The packet to decode
     */
    public static void decode(IMessageProcessor messageProcessor, DatagramPacket packet) {
        decode(messageProcessor, packet, Message.MESSAGE_SIZE);
    }

    /**
     * Decode message
     * @param messageProcessor The processor which will process the message
     * @param packet The packet to decode
     * @param messageSize The message length
     */
    public static void decode(IMessageProcessor messageProcessor, DatagramPacket packet, int messageSize) {
        ByteBuffer byteBuffer = ByteBuffer.allocate(messageSize).put(packet.getData());
        byteBuffer.position(0);
        byte type = byteBuffer.get();
        byte id = byteBuffer.get();
        long time = byteBuffer.getLong();

        if(type == Configuration.getMessageSyncType()) {
            messageProcessor.process(new MessageSync(id, packet.getAddress(), packet.getPort()));
        }
        else if(type == Configuration.getMessageFollowUpType()) {
            messageProcessor.process(new MessageFollowUp(id, time, packet.getAddress(), packet.getPort()));
        }
        else if(type == Configuration.getMessageDelayRequestType()) {
            messageProcessor.process(new MessageDelayRequest(id, packet.getAddress(), packet.getPort()));
        }
        else if(type == Configuration.getMessageDelayResponseType()) {
            messageProcessor.process(new MessageDelayResponse(id, time, packet.getAddress(), packet.getPort()));
        } else {
            LOG.log(Level.WARNING, "Message ignored : the message received is unknown" + System.lineSeparator());
        }
    }
}
