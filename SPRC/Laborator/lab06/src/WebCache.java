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
import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.LinkedList;

/**
 * Clasa ce implementeaza un cache de web
 *
 */
public class WebCache {

	// maparea intrarilor cache curent stiute de cache-ul nostru 
	// (intrarile sunt tinute si in memorie in aceasta mapare pentru a optimiza timpul de raspuns al cache-ului)
	private Hashtable cache;
	// clasa auxiliara ce contine metodele pentru lucrul cu discul
	private WebCacheFile cacheFile;

	// timpul maxim cat o pagina poate fi folosita inainte de a se forta un refresh al continutului acestuia
	private long maxTimeToKeepPage = -1;
	// dimensiunea maxima a cache-ului 
	private long maxSizeOnDisk = -1;
	
	/**
	 * Constructorul primeste ca parametrii dimensiunea maxima pe disc si timpul maxim de pastrare a unui continut web.
	 */
	public WebCache(long maxSizeOnDisk, long maxTimeToKeepPage) {
		this.maxSizeOnDisk = maxSizeOnDisk;
		this.maxTimeToKeepPage = maxTimeToKeepPage;
		String workingDir = System.getProperty("user.home")+File.separatorChar+"cache_test";
		cacheFile = new WebCacheFile(workingDir);
		// automat este citit continutul cache anterior stocat pe disc (la o repornire cache-ul nu se pierde, se refoloseste)
		cache = cacheFile.init();
	}
	
	/**
	 * Singura metoda pusa la dispozitie de cache - intoarce continutul unei pagini web pe baza unei adrese primita ca parametru
	 * @param url
	 * @return
	 */
	public String requestURL(String url) {
		// stergem in mod automat intrarile prea vechi a mai fi valabile
		purgeOldPages();
		if (cache.containsKey(url)) { // daca deja avem in cache continutul
			System.out.println("[HIT] url: " + url);
			return ((WebCacheEntry)cache.get(url)).getContent(); // atunci returnam valoarea din memorie
		}
		System.out.println("[MISS] url: " + url);
		// altfel facem o interogare a adresei pentru continutul fresh al paginii web
		String content = getWebPage(url);
		if (content == null) // daca interogarea a esuat 
			return content;
		// formam o noua intrare cache
		WebCacheEntry entry = new WebCacheEntry(url);
		entry.setContent(content);
		// o adaugam intre intrarile pastrate in memorie
		cache.put(url, entry);
		// si o scriem si pe disc pentru toleranta la defecte - la o repornire vom avea inca acces la intrarea cache
		cacheFile.updateEntry(entry);
		System.out.println("Cache: " + cache.toString());
		// verificam daca cu ce am adaugat in cache nu am depasit dimensiunea maxima a cache-ului pe disc
		if (maxSizeOnDisk > 0l) {
			long sizeOnDisk = cacheFile.getSizeOnDisk();
			while (sizeOnDisk > maxSizeOnDisk) { // cat timp am depasit mai stergem intrari
				// remove the oldest accessed entry ...
				WebCacheEntry wce = null;
				for (Enumeration en = cache.keys(); en.hasMoreElements(); ) {
					String su = (String)en.nextElement();
					WebCacheEntry e = (WebCacheEntry)cache.get(su);
					if (wce == null) wce = e;
					else {
//						if (wce.getLastRead() > e.getLastRead()) wce = e; // alegem pagina cea mai veche accesata pentru stergere (LRU)
						if (wce.getNbAccesses() >= e.getNbAccesses() && !e.getURL().equals(entry.getURL())) {
							wce = e; // LFU
						}
					}
				}
				if (wce == null) break;

				System.out.println("Removing " + wce.getURL() + " access number: " + wce.getNbAccesses());

				// stergem respectiva intrare din cache
				cache.remove(wce.getURL());
				cacheFile.removeEntry(entry);
				long newSizeOnDisk = cacheFile.getSizeOnDisk();
				if (sizeOnDisk == newSizeOnDisk) break;
				sizeOnDisk = newSizeOnDisk;
			}
		}
		return content;
	}
	
	/**
	 * Metoda se foloseste pentru a sterge intrarile din cache ce sunt prea vechi... prin stergere fortam o actualizare a continutului paginii
	 */
	private void purgeOldPages() {
		if (maxTimeToKeepPage <= 0l) return;
		long currentTime = System.currentTimeMillis();
		LinkedList toRemove = new LinkedList();
		for (Enumeration en = cache.keys(); en.hasMoreElements(); ) {
			String url = (String)en.nextElement();
			WebCacheEntry entry = (WebCacheEntry)cache.get(url);
			long diff = currentTime - entry.getLastWrite();
			if (diff > maxTimeToKeepPage) {
				toRemove.addLast(url);
				cacheFile.removeEntry(entry);
			}
		}
		for (Iterator it = toRemove.iterator(); it.hasNext(); ) {
			String url = (String)it.next();
			cache.remove(url);
		}
	}
	
	/**
	 * Metoda ce intoarce o pagina web pe unei adrese web - interogare a serverului web de la respectiva adresa
	 * @param u Adresa web
	 * @return Continutul paginii web corespunzatoare
	 */
	private String getWebPage(String u) {
		URL url;
		try { 
			url = new URL(u);
		} catch (MalformedURLException e) {
			System.err.println("ERROR: invalid URL " + u);
			return null;
		}
		// ne limitam la protocolul http - pana la urma asta e un cache web
		if (url.getProtocol().compareTo("http") != 0) 
			return null;
		try {
			// incercam accesarea URL-ului
			URLConnection urlConnection = url.openConnection();
//			urlConnection.setConnectTimeout(10 * 1000);
			urlConnection.setAllowUserInteraction(false);
			InputStream urlStream = url.openStream();
			// si citirea continutului paginii web de la respectiva adresa
			byte b[] = new byte[1000];
			int numRead = urlStream.read(b);
			String content = new String(b, 0, numRead);
			while (numRead != -1) {
				numRead = urlStream.read(b);
				if (numRead != -1) {
					String newContent = new String(b, 0, numRead);
					content += newContent;
				}
			}
			urlStream.close();
			return content;
		} catch (IOException e) {
			System.err.println("ERROR: couldn't open URL " + u);
		}
		return null;
	}
	
} // end of class WebCache

