package lab3;

public class Circle extends Form {

	float radius;
	
	public Circle() {
		
	}
	
	public Circle(String color, float radius) {
		super(color);
		this.radius = radius;
	}
	
	@Override
	public float getArea() {
		return (float)(Math.PI) * this.radius * this.radius;
	}
	
	@Override
	public String toString() {
		return "Cerc: " + super.toString() + " " + getArea();
	}
	
	public void printCircleDimensions() {
		System.out.println("radius = " + this.radius);
	}
	
	@Override
	public void action() {
		printCircleDimensions();
	}
}
