package lab01;

public class Operations {
	
	public static ComplexNumber add(ComplexNumber x, ComplexNumber y) {
		
		return new ComplexNumber(x.re + y.re, x.im + y.im);	
	}
	
	public static ComplexNumber multiplication(ComplexNumber x, ComplexNumber y) {
		
		return new ComplexNumber(x.re * y.re - x.im * y.im, x.re * y.im + y.re * x.im);
	}
	
	public static void main(String[] args) {
		
		ComplexNumber x = new ComplexNumber(-2, 5);
		ComplexNumber y = new ComplexNumber(1, -2);
		
		ComplexNumber ans1 = add(x, y);
		ComplexNumber ans2 = multiplication(x, y);
		
		ans1.printNumber();
		ans2.printNumber();
	
	}

}
