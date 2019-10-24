package Common.MessageManager;

import Common.Message.ProtocolMessage.MessageDelayRequest;
import Common.Message.ProtocolMessage.MessageDelayResponse;
import Common.Message.ProtocolMessage.MessageFollowUp;
import Common.Message.ProtocolMessage.MessageSync;

/**
 * @File        : IMessageProcessor.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Define method that a message processor must implement
 *
 * @Comment(s)  : -
 */
public interface IMessageProcessor {
    /**
     * Process a MessageSync type message
     * @param messageSync The MessageSync to process
     */
    void process(MessageSync messageSync);

    /**
     * Process a MessageFollowUp type message
     * @param messageFollowUp The MessageFollowUp to process
     */
    void process(MessageFollowUp messageFollowUp);

    /**
     * Process a MessageDelayRequest type message
     * @param messageDelayRequest The MessageDelayRequest to process
     */
    void process(MessageDelayRequest messageDelayRequest);

    /**
     * Process a MessageDelayResponse type message
     * @param messageDelayResponse The MessageDelayResponse to process
     */
    void process(MessageDelayResponse messageDelayResponse);
}
