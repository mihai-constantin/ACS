package lab01;

public class BookstoreCheck {
	
	public static boolean duplicate(Book b1, Book b2) {
	
		return b1.equals(b2);
	}
	
	public static Book morePages(Book b1, Book b2) {
		
		if(b1.pageCount > b2.pageCount) {
			return b1;
		}
		
		return b2;
	}
	
	public static void main(String[] args) {
		
		Book b1 = new Book("Mara", "Slavici", "art", 231);
		Book b2 = new Book("Mara", "Slavici", "art", 231);
		
		System.out.println("Duplicates? : " + duplicate(b1, b2));
		System.out.println("Book with more pages : " + morePages(b1, b2));
		
	}

}
