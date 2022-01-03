package lab2;

import java.util.Random;

public class RandomStringGenerator {
	
	private int length;
	private String s;
	
	public RandomStringGenerator(int length, String s) {
		this.length = length;
		this.s = s;
	}
	
	public String next() {
		
		char[] c = new char[length];
		
		Random generator = new Random();
		for(int i = 0; i < length; i++) {
			int value = generator.nextInt(s.length());
			c[i] = s.charAt(value);
		}
		
		return new String(c);
	}
	
	public static void main(String[] args) {
		
		RandomStringGenerator myGenerator1 = new RandomStringGenerator(5, "abcdef");
		
		for(int i = 0; i < 5; i++) {
			System.out.println(myGenerator1.next());
		}
		
		System.out.println("");
		
		RandomStringGenerator myGenerator2 = new RandomStringGenerator(4, "def");
		
		for(int i = 0; i < 5; i++) {
			System.out.println(myGenerator2.next());
		}
		
	}

}
