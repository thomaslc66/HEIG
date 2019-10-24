package Common;

/**
 * @File        : IdGenerator.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Use to generate id for packets
 *
 * @Comment(s)  : -
 *
 * @See         : IMessageProcessor
 */
public class IdGenerator {
    private byte generatedClientId = 0;

    /**
     * Get the next id for packet
     * @return The next id for packet
     */
    public byte generateID(){
        generatedClientId++;
        return generatedClientId;
    }
}
