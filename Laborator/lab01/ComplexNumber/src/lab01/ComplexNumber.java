package lab01;

public class ComplexNumber {
	
	float re;
	float im;
	
	public ComplexNumber(float re, float im) {
		this.re = re;
		this.im = im;
	}
	
	public void printNumber() {
		System.out.println(re + ((im < 0) ? "" : "+") + im + "i");
	}

}
