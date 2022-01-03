package bash;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Scanner;

public final class Bash {
	
    private Path currentDirectory;
    private StringBuffer history;

    private CommandPublisher publisher;
    private static final String EXIT = "exit";

    public Bash() {   
    	
    	history = new StringBuffer();
    	currentDirectory = Paths.get("").toAbsolutePath();

        // Instantiate a new command publisher
        publisher = new BashCommandPublisher();
        
        // CommandSubscribers know how to execute the commands.
        // Subscribe some to the Command publisher.
		
		BashUtils bashUtils = new BashUtils();
		
		BashUtils.Echo echo = bashUtils.new Echo();
		publisher.subscribe(echo);
		
		BashUtils.Cd cd = bashUtils.new Cd();
		publisher.subscribe(cd);
		
		BashUtils.Pwd pwd = bashUtils.new Pwd();
		publisher.subscribe(pwd);
		
		BashUtils.Ls ls = bashUtils.new Ls();
		publisher.subscribe(ls);
		
		BashUtils.Histoy history = bashUtils.new Histoy();
		publisher.subscribe(history);
    }

    public void start() {
    	
        Scanner scanner = new Scanner(System.in);

        while (true) {
        	
            // Read commands from the command line
            final String input = scanner.nextLine();
            
            Command currentCommand = new Command(input, this);

            // If we read the "exit" string then we should stop the program.
            if(input.equals(EXIT)) {
            	scanner.close();
            	System.exit(0);
            }

            // Create an anonymous class which extends Thread.
            // It has to implement the 'run' method. From the 'run' method publish the command
            // so that the CommandSubscribers start executing it.
            // Don't forget to start the thread by calling the 'start' method on it!
            
            Thread t = new Thread() {
            	@Override
            	public void run() {            		
            		publisher.publish(currentCommand);
            		
            	}
            };
            
            t.start();

        }
    }

    // Create an inner class which implements the CommandPublisher interface.
    // 1. The class should contain an ArrayList of CommandSubscribers
    // 2. The class should implement the subscribe and publish methods.
    
    class BashCommandPublisher implements CommandPublisher {
    	
    	ArrayList<CommandSubscriber> list = new ArrayList<CommandSubscriber>();

		@Override
		public void subscribe(CommandSubscriber subscriber) {
			list.add(subscriber);
		}

		@Override
		public void publish(Command command) {
			for(CommandSubscriber subscriber : list) {
				subscriber.executeCommand(command);
			}
		}
    	
    }
    
    public Path getCurrentDirectory() {
		return currentDirectory;
	}
    
    public void setCurrentDirectory(Path currentDirectory) {
		this.currentDirectory = currentDirectory;
	}
    
    public StringBuffer getHistory() {
		return history;
	}
    
    public void setHistory(StringBuffer history) {
		this.history = history;
	}

}
