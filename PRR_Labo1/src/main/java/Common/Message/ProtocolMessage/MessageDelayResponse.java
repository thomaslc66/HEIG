package Common.Message.ProtocolMessage;

import Common.Configuration.Configuration;
import Common.Message.Message;

import java.net.InetAddress;

/**
 * @File        : MessageDelayResponse.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Define delay respond message
 *
 * @Comment(s)  : -
 *
 * @See         : Message
 */
public class MessageDelayResponse extends Message {
    public MessageDelayResponse(byte id, long time, InetAddress address, int port) {
        super(Configuration.getMessageDelayResponseType(), id, time, address, port);
    }
}
