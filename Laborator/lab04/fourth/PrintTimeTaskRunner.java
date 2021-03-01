package fourth;

import java.util.Calendar;

import first.Task;
import third.Strategy;

public class PrintTimeTaskRunner extends AbstractTaskRunner {

	public PrintTimeTaskRunner(Strategy strategy) {
		super(strategy);
	}

	@Override
	protected void afterExecution(Task task) {
		
		Calendar c = Calendar.getInstance();
		System.out.println("Hour of day : " + c.get(Calendar.HOUR_OF_DAY) + ":" + 
				c.get(Calendar.MINUTE) + ":" + c.get(Calendar.SECOND));
	}
	
	@Override
	public String toString() {
		return "PrintTimeTaskRunner - LIFO";
	}

}
