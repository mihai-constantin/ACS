package bash;

public interface CommandPublisher {

    /**
     * Subscribe a CommandSubscriber to this Publisher so that it is
     * notified when a command is received.
     */
    void subscribe(CommandSubscriber subscriber);

    /**
     * Publish a Command to all registered subscribers.
     * Usually by calling the method defined in the CommandSubscriber interface.
     */
    void publish(Command command);
}
