package bash;

public class Command {
	
    private Bash bash;
    private String command;

    public Command(final String newCommand, final Bash newBash) {
        this.bash = newBash;
        this.command = newCommand;
    }

    public final Bash getBash() {
        return bash;
    }

    public final String getCommand() {
        return command;
    }
}
