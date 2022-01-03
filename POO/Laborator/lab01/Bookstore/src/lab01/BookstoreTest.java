package lab01;

import java.util.Scanner;

public class BookstoreTest {
	
	public static void main(String[] args) {
		
		Book book = new Book();
		
		Scanner s = new Scanner(System.in);
		
		System.out.print("BOOK_TITLE : ");
		book.title = s.nextLine();
		System.out.print("BOOK_AUTHOR : ");
		book.author = s.nextLine();
		System.out.print("BOOK_PUBLISHER : ");
		book.publisher = s.nextLine();
		System.out.print("BOOK_PAGES : ");
		book.pageCount = s.nextInt();
		
		s.close();
		
		if(book.pageCount <= 0) {
			System.out.println("Numar de pagini invalid !");
			return;
		}
		
		System.out.println(book);
	}

}
