package commands;

import java.util.Stack;

public class CommandManager {

    /* - void undo()
       - void redo()
       - void executeCommand(Command c)
       - maybe check if undo() and redo() are available ?
             -> check GameState class, see the errors
       - keep track of the commands somehow
    */

    Stack<Command> stackUndo = new Stack<>();
    Stack<Command> stackRedo = new Stack<>();

    public void executeCommand(Command c) {
        stackUndo.add(c);
        c.execute();
    }

    public void undo() {
        Command c = stackUndo.pop();
        stackRedo.add(c);
        c.undo();
    }

    public void redo() {
        Command c = stackRedo.pop();
        stackUndo.add(c);
        c.execute();
    }

    public boolean isUndoAvailable() {
        return !stackUndo.empty();
    }

    public boolean isRedoAvailable() {
        return !stackRedo.empty();
    }
}
