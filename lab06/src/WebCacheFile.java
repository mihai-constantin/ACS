/**
	Sisteme de programe pentru retele de calculatoare
	
	Copyright (C) 2008 Ciprian Dobre & Florin Pop
	Univerity Politehnica of Bucharest, Romania

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 */

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.URL;
import java.util.Hashtable;

/**
 * Clasa ce contine metode auxiliare pentru accesarea intrarilor din cache pe discul local.
 *
 */
public class WebCacheFile {

	// unde sunt scrise pe disc intrarile cache-ului
	private String workingDir;
	
	/**
	 * Constructorul.
	 * @param workingDir Clasa se instantieaza cu un anumit director de lucru corespunzator intrarilor cache.
	 */
	public WebCacheFile(String workingDir) {
		this.workingDir = workingDir;
		// verifica si directorul
		try {
			File f = new File(workingDir);
			if (!f.exists()) { // daca inca nu exista directorul de cache
				f.mkdirs(); // atunci acesta este creat
			} else if (f.exists() && !f.isDirectory()) { // daca deja exista, dar desemneaza un fisier
				try {
					File nf = File.createTempFile(workingDir, "tmp");
					byte b[] = new byte[1024];
					int nb;
					FileOutputStream fos = new FileOutputStream(nf);
					FileInputStream fis = new FileInputStream(f);
					while ((nb = fis.read(b)) > 0) {
						fos.write(b, 0, nb);
						fos.flush();
					}
					fos.close();
					fis.close();
					System.err.println("File "+workingDir+" already exists, renamed to "+nf.getAbsolutePath());
				} catch (Throwable t) {
					t.printStackTrace();
					System.exit(-1);
				}
				f.delete(); // atunci acesta este sters
				f.mkdirs(); // si se creaza un director pentru intrarile de cache
			}
		} catch (Exception e) { }
	}
	
	/**
	 * Metoda care se apeleaza pentru a citi toate intrarile de cache ce exista
	 * curent pe disc.
	 * @return Un cache in memorie al intrarilor ce exista pe disc
	 */
	public Hashtable init() {
		Hashtable h = new Hashtable();
		File f = new File(workingDir);
		if (!f.exists() || !f.isDirectory()) // daca a aparut o problema si nu exista directorul de cache 
			return h;
		File fs[] = f.listFiles(); // intoarce continutul directorului de cache
		if (fs == null || fs.length == 0) // daca momentan nu exista nici o intrare 
			return h;
		for (int i=0; i<fs.length; i++) { // pentru fiecare intrare reface intrarea cache in memorie 
			if (!fs[i].isFile()) { // daca am gasit un director
				continue; // nu e de interes, il sarim
			}
			// altfel incercam si citim continutul intrarii cache in memorie
			try {
				ObjectInputStream ois = new ObjectInputStream(new FileInputStream(fs[i]));
				WebCacheEntry entry = (WebCacheEntry)ois.readObject();
				h.put(entry.getURL(), entry);
				ois.close();
			} catch (Exception e) { 
				// in acest caz am gasit un fisier corupt continand o intrare cache
				// il stergem cu totul pentru ca el nu prezinta interes
				fs[i].delete();
			}
		}
		return h;
	}
	
	/**
	 * Metoda ce intoarce dimensiunea curenta a spatiului pe disc ocupat de cache.
	 */
	public long getSizeOnDisk() {
		long size = 0l;
		File f = new File(workingDir);
		if (!f.exists() || !f.isDirectory()) return size;
		File fs[] = f.listFiles();
		if (fs == null || fs.length == 0) return size;
		for (int i=0; i<fs.length; i++) {
			if (!fs[i].isFile()) {
				fs[i].delete();
				continue;
			}
			size += fs[i].length();
		}
		return size;
	}

	/**
	 * Metoda apelata pentru actualizarea pe disc a unei intrari cache
	 * @param entry Noua intrare ce se doreste actualizata si pe disc
	 */
	public void updateEntry(WebCacheEntry entry) {
		String fileName = workingDir+File.separatorChar+formName(entry);
		File f = new File(fileName);
		if (f.exists()) // vechiul fisier, daca deja exista, este sters... 
			f.delete();
		// scriem continutul pe disc
		try {
			ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(f));
			oos.writeObject(entry);
			oos.flush();
			oos.close();
		} catch (Exception e) { 
			e.printStackTrace();
		}
	}
	
	/**
	 * Metoda auxiliara pentru stergerea unei intrari cache de pe disc.
	 * @param entry Intrarea ce se doreste a fi inlaturata.
	 */
	public void removeEntry(WebCacheEntry entry) {
		String fileName = workingDir+File.separatorChar+formName(entry);
		File f = new File(fileName);
		f.delete();
	}
	
	/**
	 * Metoda auxiliara ce genereaza un nume de fisier intrare cache pe baza
	 * adresei URL corespunzatoare respectivei intrari
	 * @param entry Intrarea cache
	 * @return Numele corespunzator fisierului pe disc
	 */
	private String formName(WebCacheEntry entry) {
		try {
			URL u = new URL(entry.getURL());
			return u.getHost()+"_"+(u.getPort() > 0 ? u.getPort()+"_" : "")+u.getPath().replace(File.separatorChar, '_');
		} catch (Throwable t) {
			t.printStackTrace();
			return entry.getURL();
		}
	}
	
} // end of class WebCacheFile


