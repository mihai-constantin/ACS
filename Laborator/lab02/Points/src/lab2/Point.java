package lab2;

public class Point {
	
	private float x;
	private float y;
	
	public Point() {
		
	}
	
	public Point(float x, float y) {
		this.x = x;
		this.y = y;
	}
	
	public void setX(float x) {
		this.x = x;
	}
	
	public void setY(float y) {
		this.y = y;
	}
	
	public void changeCoords(float x, float y) {
		this.x = x;
		this.y = y;
	}
	
	public void write() {
		System.out.println("(" + x + ", " + y + ")");
	}
	
	public static void main(String[] args) {
		
		Point p1 = new Point(2.5f, 3f);
		p1.write();
		p1.changeCoords(2f, 1.5f);
		p1.write();
		
		System.out.println("");
		
		Point p2 = new Point(-2.5f, 4f);
		p2.write();
		p2.changeCoords(3.4f, 1.7f);
		p2.write();
	}

}
