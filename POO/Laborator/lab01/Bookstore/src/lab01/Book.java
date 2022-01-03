package lab01;

public class Book {
	
	String title;
	String author;
	String publisher;
	int pageCount;
	
	public Book() {
		
	}
	
	public Book(String title, String author, String publisher, int pageCount) {
		this.title = title;
		this.author = author;
		this.publisher = publisher;
		this.pageCount = pageCount;
	}
	
	public String toString() {
		return this.title.toUpperCase() + ", " + this.author.substring(0, 1).toUpperCase() + this.author.substring(1).toLowerCase() + ", " 
				+ this.publisher.toLowerCase() + ", " + this.pageCount;
	}
	
	public boolean equals(Object o) {
		Book b = (Book) o;
		return title.equals(b.title) && author.equals(b.author) 
				&& publisher.equals(b.publisher) && pageCount == b.pageCount;
	}

}
