package lab2;

public class Polygon {
	
	private int n;
	private Point[] points;
	
	public Polygon(int n) {
		this.n = n;
		
		this.points = new Point[n];
		for(int i = 0; i < n; i++) {
			this.points[i] = new Point();
		}
	}
	
	public Polygon(float[] array) {
		this(array.length / 2);
		
		for(int i = 0; i < n; i++) {
			this.points[i].setX(array[2 * i]);
			this.points[i].setY(array[2 * i + 1]);
		}
	}
	
	public static void main(String[] args) {
		
		Polygon p1 = new Polygon( new float[] {1f, 1f, 2f, 1.5f, 3f, 0.5f} );
		
		System.out.println("Number of points : " + p1.n);
		
		for(int i = 0; i < p1.n; i++) {
			p1.points[i].write();
		}
		
		System.out.println("");
		
		Polygon p2 = new Polygon( new float[] {1.5f, 1.5f, 2.5f, 2f, 3.5f, 1f, 2.2f, 4.3f} );
		
		System.out.println("Number of points : " + p2.n);
		
		for(int i = 0; i < p2.n; i++) {
			p2.points[i].write();
		}
	}

}
