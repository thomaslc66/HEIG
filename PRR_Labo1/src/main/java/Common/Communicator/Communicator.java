package Common.Communicator;

import java.net.DatagramSocket;

/**
 * @File        : Communicator.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Basic structure to create Sender and Receiver
 *
 * @Comment(s)  : -
 *
 */
abstract class Communicator {
    private DatagramSocket socket;

    public Communicator(DatagramSocket socket) {
        this.socket = socket;
    }

    protected DatagramSocket getSocket() {
        return socket;
    }
}
