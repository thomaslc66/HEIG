package Common.Message.ProtocolMessage;

import Common.Configuration.Configuration;
import Common.Message.Message;

import java.net.InetAddress;

/**
 * @File        : MessageDelayRequest.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Define delay request message
 *
 * @Comment(s)  : -
 *
 * @See         : Message
 */
public class MessageDelayRequest extends Message {
    public MessageDelayRequest(byte id, InetAddress address, int port) {
        super(Configuration.getMessageDelayRequestType(), id, 0, address, port);
    }
}
