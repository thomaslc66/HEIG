package Common.MessageManager;

import Common.IdGenerator;

/**
 * @File        : MessageManager.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Define a basic structure of MessageManager
 *
 * @Comment(s)  : -
 *
 * @See         : IMessageProcessor
 */
public abstract class MessageManager implements IMessageProcessor {

    private IdGenerator idGenerator;

    public MessageManager() {
        this.idGenerator = new IdGenerator();
    }

    /**
     * Generate the next id for packet
     * @return The next id for packet
     */
    public byte generateID() {
        return idGenerator.generateID();
    }

    /**
     * Use to ask to MessageManager to send special message pattern for synchronisation
     */
    public abstract void sendSynchronisationMessage();
}
