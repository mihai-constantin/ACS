package lab3;

public class Triangle extends Form {
	
	float height;
	float base;
	
	public Triangle() {
		
	}
	
	public Triangle(String color, float height, float base) {
		super(color);
		this.height = height;
		this.base = base;
	}
	
	@Override
	public float getArea() {
		return (this.base * this.height ) / 2;
	}
	
	@Override
	public String toString() {
		return "Triunghi: " + super.toString() + " " + getArea();
	}
	
	@Override
	public boolean equals(Object obj) {
		
		Triangle t = (Triangle) obj;
		
		return color.equals(t.color) && (Math.abs(height - t.height) < eps) && (Math.abs(base - t.base) < eps); 
	}
	
	public void printTriangleDimensions() {
		System.out.println("heigth = " + this.height + ", " + "base = " + this.base);
	}
	
	@Override
	public void action() {
		printTriangleDimensions();
	}

}
