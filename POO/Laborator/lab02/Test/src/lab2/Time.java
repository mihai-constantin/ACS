package lab2;

public class Time {
	
	Integer x;
	int y;
	
	public void f() {
		x = new Integer(2 + 3);
	}
	
	private long runInteger() {
		long start = System.nanoTime();
		f();
		return System.nanoTime() - start;
	}
	
	public void g() {
		y = 2 + 3;
	}
	
	private long runInt() {
		long start = System.nanoTime();
		g();
		return System.nanoTime() - start;
	}

	public static void main(String[] args) {
		
		Time t = new Time();
		
		System.out.println("Integer : " + t.runInteger());
		System.out.println("Int : " + t.runInt());
	}
}
