package lab2;

public class PasswordMaker {
	
	private static final int MAGIC_NUMBER = 7;
	private final String MAGIC_STRING;
	
	private String firstName;
	private String lastName;
	private int age;
	
	
	public PasswordMaker(String firstName, String lastName, int age) {
		this.firstName = firstName;
		this.lastName = lastName;
		this.age = age;
		
		RandomStringGenerator generator = new RandomStringGenerator(20, "abcdefghijklmnopqrstuvwxyz");
		MAGIC_STRING = generator.next();
	}
	
	public String getPassword() {
		
		RandomStringGenerator generator = new RandomStringGenerator(10, MAGIC_STRING);
		
		RandomStringGenerator myGenerator = new RandomStringGenerator(MAGIC_NUMBER, generator.next());
		
		String password = firstName.substring(firstName.length() - age % 3) +
				myGenerator.next() +
				String.valueOf(age + lastName.length()); 
		
		return password;
	}
	
	public static void main(String[] args) {
		
		PasswordMaker passwordMaker = new PasswordMaker("Mihai", "Constantin", 20);
		
		System.out.println(passwordMaker.getPassword());
		System.out.println(passwordMaker.getPassword());
	}

}
