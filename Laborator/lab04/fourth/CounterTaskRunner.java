package fourth;

import first.Task;
import third.Strategy;

public class CounterTaskRunner extends AbstractTaskRunner {

	public int count;
	
	public CounterTaskRunner(Strategy strategy) {
		super(strategy);
	}

	@Override
	protected void afterExecution(Task task) {
		count++;
	}
	
	public int getCounter() {
		return count;
	}
	
	@Override
	public String toString() {
		return "CounterTaskRunner - FIFO";
	}

}
