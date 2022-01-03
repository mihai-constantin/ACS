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

import java.io.Serializable;

/**
 * O intrare ce este stocata in cache-ul de pe disc
 *
 */
public class WebCacheEntry implements Serializable {
	static final long serialVersionUID = 7471069187532416589L;
	
	// url-ul de unde a fost citita intrarea
	private final String url;
	// continutul paginii de web citita de la adresa data prin url
	private String content;
	// cand a fost facuta ultima actualizare a continutului acestei intrari din cache
	private long writeDate = -1;
	// cand a fost accesata ultima data aceasta intrare
	private long readDate = -1;
	// numarul de accesari pentru o pagina
	private long accessNumber;
	
	/**
	 * Constructorul clasei.
	 * @param url Adresa corespunzatoare intrarii in cache
	 */
	public WebCacheEntry(String url) {
		this.url = url;
	}
	
	/**
	 * Metoda ce actualizeaza continutul intrarii din cache
	 * @param content Noul continut al intrarii cache
	 */
	public void setContent(String content) {
		this.content = content;
		// automat setam si data ultimei accesari si pe cea a ultimei actualizari
		writeDate = readDate = System.currentTimeMillis();
		this.accessNumber++;
	}
	
	/**
	 * Metoda intoarce data ultimei accesari a intrarii din cache.
	 */
	public long getLastRead() {
		return readDate;
	}
	
	/**
	 * Metoda intoarce data ultimei actualizari a intrarii din cache.
	 * @return
	 */
	public long getLastWrite() {
		return writeDate;
	}
	
	/**
	 * Metoda prin care se realizeaza accesarea continutului intrarii din cache.
	 */
	public String getContent() {
		// se actualizeaza si data ultimei accesari
		readDate = System.currentTimeMillis();
		this.accessNumber++;
		return content;
	}
	
	/**
	 * Intoarce adresa corespunzatoare intrarii din cache.
	 */
	public String getURL() {
		return url;
	}

	public long getNbAccesses() {
		return this.accessNumber;
	}
	
} // end of class WebCacheEntry


