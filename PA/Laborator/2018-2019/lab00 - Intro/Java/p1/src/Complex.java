import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Vector;


public class Complex {
	public float r;	// Partea reala
	public float i;	// Partea imaginara

	/**
	 * Functie care citeste numere complexe dintr-un fisier
	 * @param filename	numele fisierului de intrare
	 * @return			vectorul de numere complexe
	 */
	public static Vector<Complex> readData ( String filename ) {
		BufferedReader br = null;						// pentru citire din fisier
		int n = 0;										// numar de elemente
		Vector<Complex> res = new Vector<Complex>();	// vectorul rezultat
		
		/* you should use try-catch for proper error handling! */
		try {
			String sCurrentLine;
			br = new BufferedReader(new FileReader(filename));
			
			/* citim numarul de elemente */
			sCurrentLine = br.readLine();
			n = Integer.parseInt(sCurrentLine);
			
			/* citim pe rand fiecare element */
			for (int i=0; i<n; i++) {
				sCurrentLine = br.readLine();
				Complex current = new Complex();
				current.r = Integer.parseInt(sCurrentLine.split(" ")[0]);
				current.i = Integer.parseInt(sCurrentLine.split(" ")[1]);
				res.add(current);
			}
		} catch (Exception e) {		
			e.printStackTrace();
		} finally { 					
			/* trebuie sa inchidem buffered reader-ul */
			try {
				if (br != null) br.close();
			} catch (IOException ex) {
				ex.printStackTrace();
			}
		}
		
		return res;
	}
	
	/**
	 * Functie care afiseaza pe ecran elementele unui vector de numere complexe
	 * @param v		vectorul de numere complexe
	 */
	public static void writeVector ( Vector<Complex> v ) {
		for (Complex element : v) {
			System.out.println(element);
		}
	}
	
	/**
	 * Functie care afiseaza pe ecran numarul complex
	 */
	@Override
	public String toString() {
		return String.format("(%.2f, %.2f)", r, i);
	}

}