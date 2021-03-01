package lab3;

public class Main {
	
	public static void main(String[] args) {
		
		Form[] form = new Form[2];
		
		form[0] = new Triangle("albastru", 5f, 4f);
		form[1] = new Circle("rosu", 2f);
		
		System.out.println(form[0]);
		System.out.println(form[1]);
		
		Form triangle = new Triangle("albastru", 5f, 4f);
		System.out.println("duplicates: " + form[0].equals(triangle));
		
		for(Form f : form) {
			
//			if(f instanceof Triangle) {
//				((Triangle) f).printTriangleDimensions();
//			}
//			
//			if(f instanceof Circle) {
//				((Circle) f).printCircleDimensions();
//			}
			
			f.action();
		}
		
	}

}
