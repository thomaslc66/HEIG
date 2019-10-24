package Common.Message.ProtocolMessage;

import Common.Configuration.Configuration;
import Common.Message.Message;

import java.net.InetAddress;

/**
 * @File        : MessageFollowUp.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Define follow up message
 *
 * @Comment(s)  : -
 *
 * @See         : Message
 */
public class MessageFollowUp extends Message {
    public MessageFollowUp(byte id, long time, InetAddress address, int port) {
        super(Configuration.getMessageFollowUpType(), id, time, address, port);
    }
}
