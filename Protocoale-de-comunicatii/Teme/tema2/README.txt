CONSTANTIN MIHAI | 321CD

TEMA 2 | PROTOCOALE DE COMUNICATII
Aplicatie client-server TCP si UDP pentru gestionarea mesajelor

Aplicatia este organizata astfel:

-> server.cpp - serverul aplicatiei cu rolul de broker 
				(componenta de intermediere) in platforma de gestionare a 
				mesajelor

-> subscriber.cpp - client-ul TCP care poate sa se aboneze sau sa se dezaboneze
					de la diverse topicuri

-> helper.h - fisier header in care este definita o structura Message_UDP care
			  reprezinta formatul mesajelor clientilor UDP (topic, tip de date
			  si continut)

-> Makefile - contine regulile pentru rularea server-ului si a clientului TCP,
			  precum si o regula de clean

-> folder-ul pcom_hw2_udp_client: contine clientul UDP, pus la dispozitie de
								  echipa de asistenti.


------------------------------
IMPORTANT! - EXEMPLU DE RULARE
------------------------------

Aplicatia se ruleaza cu comanda make.
In continuare, trebuie rulat server-ul cu comanda make run_server.
Adresa IP setata din Makefile are valoarea 127.0.0.1, iar cea a portului pe
care asculta serverul este 1200.
La rulari consecutive, se recomanda schimbarea portului din Makefile.
Serverul este in acest moment deschis, iar clientii se pot conecta la el.
Un client se poate conecta la server prin urmatoarea comanda:
	./subscriber <id_client> 127.0.0.1 1200

Exemplu: ./subscriber mihai 127.0.0.1 1200

Ca urmare a acestei comenzi, in terminalul in care este rulat server-ul, se va
afisa un mesaj de forma: New client mihai connected from 127.0.0.1:<PORT>.
Se pot conecta mai multi clienti, prin deschiderea mai multor terminale, iar
la conectarea fiecarul client prin comanda de mai sus, in server se va afisa un
mesaj de notificare.
Clientul se poate deconecta, prin comanda exit, caz in care in consola 
serverului se va afisa un mesaj de forma: Client <id_client> disconnected.

Exemplu: Client mihai disconnected.

Fiecare client are posibilitatea de a se abona sau dezabona la diverse topice,
prin urmatoarele comenzi:
- subscribe <topic> <SF>
- unsubscribe <topic>

Dupa rularea acestei comenzi, se va afisa un mesaj de notificare in consola
fiecarui client cu privire la modificarea produsa:
- subscribed <topic>
- unsubscribed <topic>

Pentru a retine clientii care s-au abonat la diverse topice, am folosit un
unordered_map <string, vector<string>> subscriptions, unde cheia este
reprezentata de topicul la care clientii sunt abonati, iar valoarea este data
de vectorul care contine id-urile clientilor abonati la topicul respectiv.

Printr-o abordare similare, tot prin folosirea unui unordered_map de forma
unordered_map<int, string> umap1, am reusit sa fac asocieri intre socket-ul 
fiecarul client si id-ul sau. Acest lucru este folosit in momentul in care
afisez mesajele cand un client s-a conectat sau s-a deconectat.

In momentul in care introduc de la tastatura comanda exit in fereastra in care
este rulat server-ul, acesta se va inchide si fiecare client TCP conectata la
momentul respectiv va fi inchis. Se va afisa in fereastra fiecarui client un
mesaj de forma: Server disconnected.

Daca intram in folder-ul pcom_hw2_udp_client, putem rula si clientul UDP. Acest
lucru se realizeaza prin urmatoarea comanda:
python3 udp_client.py --mode manual 127.0.0.1 1200, daca consideram portul
pe care asculta serverul egal cu 1200.

La introducerea unui numar din intervalul 0-15, se va afisa pentru fiecare 
client TCP abonat la topic-ul respectiv un mesaj de forma: 
127.0.0.1:<PORT> - <topic> - <type> - <value>.

Asadar, daca avem mai multi clienti TCP abonati la un topic, fiecare dintre ei
va primi o notificare. Daca nu avem niciun abonat la un topic de la numarul
respectiv (un numar din intervalul 0-15), se va afisa doar in consola 
server-ului.

------------------------
Tratare comenzi invalide
------------------------

Daca clientul TCP nu va introduce de la tastatura comenzile care respecta
formatul impus se va afisa urmatorul mesaj:
Usage: subscribe <topic> <SF>
Usage: unsubscribe <topic>

---------------------------------
DETALII SUPLIMENTARE IMPLEMENTARE
---------------------------------

Pentru a retine formatul mesajelor clientilor UDP am folosit o structura 
Message_UDP, definita in helper.h. Aceasta contine topic-ul, tipul de date si
un union care contine structurile corespunzatoare in functie de tipul de date.
Am folosit de asemenea pragma pack(1) pentru a evita crearea padding-ului.

---------------------------
DEZACTIVARE ALGORITM NEAGLE
---------------------------
Pentru ca toate comenzile si mesajele trimise in platforma sa isi produca
efectul imediat, am dezactivat algoritmul Neagle, dupa crearea socketilor
pentru clientii TCP.

---------------
STORE & FORWARD
---------------

Am creat un map care asociaza fiecarui id al unui client, o valoare booleana
cu urmatoarea semnificatie: daca clientul este conectat la server la momentul
respectiv, valoarea este 1 si 0 in caz contrar.
De asemenea, am folosit un map care realizeaza asocieri intre id-ul unui client
si o lista de perechi de forma: (topic, SF).
De exemplu, daca un client este abonat la mai multe topice, este deconectat de
la server, dar clientii UDP trimit in continuare mesaje, acestea vor fi 
retinute intr-un buffer, iar in momentul in care clientul se va reconecta va 
primi mesajele respective. Acest lucru se intample, desigur in cazul SF = 1.
Daca SF = 0, nu se realizeaza store & forward.

--------------------
DETALII IMPLEMENTARE
--------------------

Tema a fost realizata pe un sistem de operare macOS Mojave 10.14.4.

