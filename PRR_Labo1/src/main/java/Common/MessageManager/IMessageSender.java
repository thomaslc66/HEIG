package Common.MessageManager;

import Common.Message.Message;

/**
 * @File        : IMessageSender.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Define method that a message sender must implement
 *
 * @Comment(s)  : -
 */
public interface IMessageSender {
    /**
     * Send message
     * @param message The message to send
     */
    void sendMessage(Message message);
}
