package bash;

import java.io.File;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;

enum Commands {
	
    CD("cd"),
    LS("ls"),
    ECHO("echo"),
    PWD("pwd"),
    HISTORY("history");

    private final String text;

    Commands(final String newText) {
        this.text = newText;
    }

    @Override
    public String toString() {
        return text;
    }
}

public class BashUtils {

    // Implement some inner classes here: Echo, Cd, Ls, History

    // example: class Cd { ... }

    // Decide if they should be static or non-static.
	
	// Create Pwd class
	class Pwd implements CommandSubscriber {

		@Override
		public void executeCommand(Command c) {
			
			final String myCommand = c.getCommand();
			
			if(!myCommand.equals(Commands.PWD.toString())) {
				return;
			}
			
			Path currentDirectory = c.getBash().getCurrentDirectory();
			
			System.out.println(currentDirectory);
			
		}
		
	}

    // Create Echo class
	class Echo implements CommandSubscriber {

		@Override
		public void executeCommand(Command c) {
			
			final String myCommand = c.getCommand();
			
			if(!myCommand.startsWith(Commands.ECHO.toString())) {
				return;
			}
			
			if(myCommand.substring(5).startsWith("\"")) {
				System.out.println(myCommand.substring(6, myCommand.length() - 1));
			}
			else {
				System.out.println(myCommand.substring(5));
			}
		}
		
	}
	

    // Create Cd class
	class Cd implements CommandSubscriber {

		@Override
		public void executeCommand(Command c) {
			
			final String myCommand = c.getCommand();
			if(!myCommand.startsWith(Commands.CD.toString())) {
				return;
			}
			
			Path currentDirectory = c.getBash().getCurrentDirectory();
			Path newCurrentDirectory = currentDirectory;
			String currentDirectoryString = currentDirectory.toString();
			
			ArrayList<String> files = new ArrayList<String>();
			
			Path cdCommand = Paths.get(myCommand.substring(3));
			
			do {
				files.add(cdCommand.getFileName().toString());
				cdCommand = cdCommand.getParent();
			}while(cdCommand != null);
			
			for(int i = files.size() - 1; i >= 0; i--) {
				
				if(files.get(i).equals("..")) {
					newCurrentDirectory = newCurrentDirectory.getParent();
					currentDirectoryString = newCurrentDirectory.toString();
				}
				else {
					currentDirectoryString = currentDirectoryString.concat(File.separator + files.get(i));
					currentDirectory = Paths.get(currentDirectoryString);
				}
			}
			
			Bash bash = c.getBash();
			
			Path newPath = Paths.get(currentDirectoryString);
			
			bash.setCurrentDirectory(newPath);
		}
		
	}

    // Create the Ls class
	class Ls implements CommandSubscriber {

		@Override
		public void executeCommand(Command c) {
			final String myCommand = c.getCommand();
			
			if(!myCommand.equals(Commands.LS.toString())) {
				return;
			}
			
			Path currentDirectory = c.getBash().getCurrentDirectory();
			
			File folder = currentDirectory.toFile();
			File[] files = folder.listFiles();
			
			for(File file : files) {
				System.out.println(file.getName());
			}
		}
		
	}

    // Create the History class
	class Histoy implements CommandSubscriber {

		@Override
		public void executeCommand(Command c) {
			
			final String myCommand = c.getCommand();
			
			Bash bash = c.getBash();
			StringBuffer history = bash.getHistory();
			
			history.append(myCommand + " | ");
			
			bash.setHistory(history);
			
			if(myCommand.equals(Commands.HISTORY.toString())) {
				System.out.println(bash.getHistory());
			}
			
		
		}
		
	}
}
