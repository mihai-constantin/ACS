package first;

import java.util.Random;

public class RandomOutTask implements Task {
	
	int number;
	static final int SIZE = 100;
	
	public RandomOutTask() {
		Random generator = new Random();
		this.number = generator.nextInt(SIZE);
	}

	@Override
	public void execute() {
		System.out.println("Numar generat: " + this.number);
		
	}

}
