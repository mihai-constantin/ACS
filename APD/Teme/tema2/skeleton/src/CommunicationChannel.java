import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * @author Constantin Mihai - 336CA
 */

/**
 * Class that implements the channel used by headquarters and space explorers to communicate.
 */
public class CommunicationChannel {

    private LinkedBlockingQueue<Message> messagesHeadQuarter = new LinkedBlockingQueue<>();
    private LinkedBlockingQueue<Message> messagesSpaceExplorer = new LinkedBlockingQueue<>();

    private ConcurrentHashMap<Long, Message> concurrentHashMap = new ConcurrentHashMap<>();

    /**
     * Puts a message on the space explorer channel (i.e., where space explorers write to and
     * headquarters read from).
     *
     * @param message message to be put on the channel
     */
    public void putMessageSpaceExplorerChannel(Message message) {
        // message to be sent by a space explorer to a HQ
        try {
            messagesSpaceExplorer.put(message);
        } catch (InterruptedException e) {

        }
    }

    /**
     * Gets a message from the space explorer channel (i.e., where space explorers write to and
     * headquarters read from).
     *
     * @return message from the space explorer channel
     */
    public Message getMessageSpaceExplorerChannel() {
        return messagesSpaceExplorer.poll();
    }

    /**
     * Puts a message on the headquarters channel (i.e., where headquarters write to and
     * space explorers read from).
     *
     * @param message message to be put on the channel
     */
    public void putMessageHeadQuarterChannel(Message message) {
        // message to be sent by a HQ to a space explorer
        if (message.getData().equals(HeadQuarter.END)) {
            return;
        }

        long threadId = Thread.currentThread().getId();
        Message concurrentHashMapMessage = concurrentHashMap.putIfAbsent(threadId, message);

        if (concurrentHashMapMessage != null) {
            // key is already map to a value -> combine these values
            Message sentMessage = new Message(concurrentHashMapMessage.getCurrentSolarSystem(),
                    message.getCurrentSolarSystem(),
                    message.getData());

            try {
                messagesHeadQuarter.put(sentMessage);
            } catch (InterruptedException e) {

            }

            // remove entry with key equals to threadId from concurrentHaspMap
            concurrentHashMap.remove(threadId);
        }
    }

    /**
     * Gets a message from the headquarters channel (i.e., where headquarters write to and
     * space explorer read from).
     *
     * @return message from the header quarter channel
     */
    public Message getMessageHeadQuarterChannel() {
        return messagesHeadQuarter.poll();
    }
}
