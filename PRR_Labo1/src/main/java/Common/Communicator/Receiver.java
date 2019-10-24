package Common.Communicator;

import Common.Encoder.MessageEncoder;
import Common.Message.Message;
import Common.MessageManager.IMessageProcessor;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

/**
 * @File        : Receiver.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 17.10.2018
 *
 * @Goal        : Basic Structure to receive packets
 *
 * @Comment(s)  : -
 *
 * @See         : Communicator, Runnable
 */
public class Receiver extends Communicator implements Runnable {
    private IMessageProcessor messageProcessor;
    private boolean isRunning = true;

    public Receiver(DatagramSocket socket, IMessageProcessor messageProcessor) {
        super(socket);
        this.messageProcessor = messageProcessor;
        new Thread(this).start();
    }

    @Override
    public void run() {
        DatagramPacket packet;
        byte[] messageContent;

        while(isRunning){
            messageContent = new byte[Message.MESSAGE_SIZE];
            packet = new DatagramPacket(messageContent, messageContent.length);
            try {
                getSocket().receive(packet);
                MessageEncoder.decode(messageProcessor, packet);
            } catch (IOException e){
                e.printStackTrace();
                this.close();
            }
        }
        this.close();
        getSocket().close();
    }

    /**
     * Use to close the receiver
     */
    protected void close() {
        this.isRunning = false;
    }
}
