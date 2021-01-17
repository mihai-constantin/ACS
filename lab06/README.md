# Laborator 6 - Consistenta datelor si toleranta la defecte

## Web cache implementat in Java
* entry point-ul programului este clasa ClientTest
    * in vectorul urls avem 3 adrese web care nu suporta https
    * pentru output-ul de mai jos s-au folosit urmatoarele valori pentru argumente
        * size: 50KB - dimensiunea maxima a web cache-ului pe disc
        * time: 20s - timpul maxim de pastrare a unui continut web
* am adaugat in clasa *WebCacheEntry* atributul accessNumber care indica numarul total de accesari pentru o pagina web
    * in momentul in care facem getContent sau setContent, atributul se incrementeaza cu 1
* politica de evazuare din cache este de tip LFU (Least Frequency Used)
    * in momentul in care se realizeaza un request, verificam daca este un MISS sau un HIT
    * daca este un MISS, requestul trebuie adaugat in cache, eliminandu-se cel cu frecventa cea mai mica
    * daca avem numai HIT- uri la un moment dat, MISS-urile vor reveni in momentul in care timpul de pastrare a paginii in cache expira
* Un exemplu de rulare a programului poate fi observat mai jos
    * la fiecare request afisam tipul acestuia (MISS/HIT), respectiv cum arata cache-ul

```
Client started with maxStorageSpace=51200 and maxTimeToKeep=20000
[MISS] http://www.gnu.org/
Cache: {http://www.gnu.org/=WebCacheEntry@5ec0a365}
[MISS] http://tvr.ro
Cache: {http://tvr.ro=WebCacheEntry@527740a2, http://www.gnu.org/=WebCacheEntry@5ec0a365}
Removing http://www.gnu.org/ access number: 1
[MISS] http://www.gnu.org/
Cache: {http://tvr.ro=WebCacheEntry@527740a2, http://www.gnu.org/=WebCacheEntry@7d907bac}
[HIT] http://www.gnu.org/
[MISS] http://www.parlament.ro/
Cache: {http://www.parlament.ro/=WebCacheEntry@3a5ed7a6, http://tvr.ro=WebCacheEntry@527740a2, http://www.gnu.org/=WebCacheEntry@7d907bac}
[HIT] http://tvr.ro
[HIT] http://www.parlament.ro/
[HIT] http://tvr.ro
[HIT] http://tvr.ro
[HIT] http://tvr.ro
[HIT] http://www.parlament.ro/
[HIT] http://tvr.ro
[HIT] http://www.parlament.ro/
[HIT] http://tvr.ro
[HIT] http://tvr.ro
[HIT] http://www.parlament.ro/
[HIT] http://tvr.ro
[HIT] http://www.parlament.ro/
[HIT] http://www.parlament.ro/
[HIT] http://tvr.ro
[HIT] http://www.gnu.org/
[HIT] http://www.gnu.org/
[HIT] http://www.parlament.ro/
[HIT] http://www.parlament.ro/
[MISS] http://www.parlament.ro/
Cache: {http://www.parlament.ro/=WebCacheEntry@67b92f0a}
[MISS] http://www.gnu.org/
Cache: {http://www.parlament.ro/=WebCacheEntry@67b92f0a, http://www.gnu.org/=WebCacheEntry@65e2dbf3}
[MISS] http://tvr.ro
Cache: {http://tvr.ro=WebCacheEntry@61f8bee4, http://www.parlament.ro/=WebCacheEntry@67b92f0a, http://www.gnu.org/=WebCacheEntry@65e2dbf3}
Removing http://www.gnu.org/ access number: 1
[HIT] http://tvr.ro
[MISS] http://www.gnu.org/
Cache: {http://tvr.ro=WebCacheEntry@61f8bee4, http://www.parlament.ro/=WebCacheEntry@67b92f0a, http://www.gnu.org/=WebCacheEntry@887af79}
[HIT] http://www.parlament.ro/
[HIT] http://tvr.ro
[HIT] http://www.parlament.ro/
[HIT] http://tvr.ro
[HIT] http://www.parlament.ro/
[HIT] http://www.parlament.ro/
[HIT] http://tvr.ro
[HIT] http://tvr.ro
[HIT] http://www.gnu.org/
[HIT] http://www.gnu.org/
[HIT] http://www.gnu.org/
[HIT] http://www.gnu.org/
[HIT] http://tvr.ro
[HIT] http://www.gnu.org/
[HIT] http://tvr.ro
[HIT] http://tvr.ro
[MISS] http://www.parlament.ro/
Cache: {http://www.parlament.ro/=WebCacheEntry@5b87ed94, http://tvr.ro=WebCacheEntry@61f8bee4, http://www.gnu.org/=WebCacheEntry@887af79}
[HIT] http://www.parlament.ro/
```