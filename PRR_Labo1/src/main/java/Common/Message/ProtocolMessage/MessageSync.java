package Common.Message.ProtocolMessage;

import Common.Configuration.Configuration;
import Common.Message.Message;

import java.net.InetAddress;

/**
 * @File        : MessageSync.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Define message sync message
 *
 * @Comment(s)  : -
 *
 * @See         : Message
 */
public class MessageSync extends Message {
    public MessageSync(byte id, InetAddress address, int port) {
        super(Configuration.getMessageSyncType(), id, 0, address, port);
    }
}
