package lab2;

public class Memory {
	
	public final static int SIZE = 100000;
	
	public static void showUsedMemory() {
		long usedMem = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
		System.out.println(usedMem);
	}
	
	public static void main(String[] args) {
		
//		String a = "abc";
//		System.out.println("String literal : " + a);
//		mem.showUsedMemory();
//		
//		String b = new String("abc");
//		System.out.println("String obtinut prin constructor : " + b);
//		mem.showUsedMemory();
		
//		String a = "abc";
//		showUsedMemory();
//		
//		String b = new String("abc");
//		showUsedMemory();
		
		
		
		String[] y = new String[SIZE];
		
		for(int i = 0; i < SIZE; i++) {
			y[i] = new String("abc");
		}
		
		showUsedMemory();
		
		String[] x = new String[SIZE];
		
		for(int i = 0; i < SIZE; i++) {
			x[i] = "def";
		}
		
		showUsedMemory();
		
		
	}

}
