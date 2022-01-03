package first;

public class CounterOutTask implements Task {

	static int count;
	
	public CounterOutTask() {
		
	}
	
	@Override
	public void execute() {
		CounterOutTask.count++;
		System.out.println(CounterOutTask.count);
		
	}
	
	

}
