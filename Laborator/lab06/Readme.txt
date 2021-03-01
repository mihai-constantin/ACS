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

Laborator 3. Consistenta datelor si toleranta la defecte.

     Listing 1. Web cache in Java.

     Aplicatia implementeaza un web cache in Java. Intrarile in cache sunt obiecte serializate de tipul
     WebCacheEntry. Intrarile sunt actualizate dupa un timp maxim ce este primit ca parametru la rularea
     aplicatiei. De asemenea pe disc sunt retinute un numar maxim de intrari astfel incat sa nu se 
     depaseasca o dimensiunea maxima a carei valoare este primita ca parametru de intrare. Regula pentru
     stergerea unor intrari este LRU (least recently used). Aceasta inseamna ca atunci cand o noua intrare
     este citita si trebuie adaugata pe disc, dar nu mai avem spatiu de stocare, automat sunt sterse intrarile
     cele mai vechi in ordinea accesarii acestora.

   Aplicatia se lanseaza in executie cu "ant". Parametrii de rulare sunt dati ca variabile in "build.xml".
   
