package fourth;

import first.Task;
import second.Container;
import third.ContainerFactory;
import third.Strategy;

public class RedoBackTaskRunner extends AbstractTaskRunner {
	
	Container c;

	public RedoBackTaskRunner(Strategy strategy) {
		super(strategy);
		c = ContainerFactory.INSTANCE.createContainer(strategy);
	}

	@Override
	protected void afterExecution(Task task) {
		c.push(task);
	}
	
	public void redo() {
		
		while(!c.isEmpty()) {
			Task task = c.pop();
			task.execute();
		}
	}
	
	@Override
	public String toString() {
		return "RedoBackTaskRunner - LIFO";
	}

}
