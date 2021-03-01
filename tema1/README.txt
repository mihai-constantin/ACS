CONSTANTIN MIHAI - 321CD

Tema implementeaza un program care efectueaza evaluarea unei expresii aritmetice in forma postfixata.
Expresia data ca input a fost memorata in variabila expr.

Am parcurs sirul caracter cu caracter, formand pe rand numerele
introduse in stiva. Am tinut cont si de numerele negative (in momentul
in care am un numar precedat de caracterul '-', la final dupa formarea
numarului scad din el dublul sau, obtinand numarul negat).

In momentul in care intalnesc un operator, efectuez doua pop-uri,
retin noul rezultat in registrul edx si dau push. Numarul de elemente
din stiva scade cu 1 la efectuarea unei astfel de operatii.

Printre cele mai importante label-uri din implementarea programului amintim:

-> convert:	formeaza numarul curent

-> minus:	efectueaza doua pop-uri
		calculeaza diferenta dintre valorile scoase
	  	pune rezultatul obtinut in stiva

-> plus:	efectueaza doua pop-uri
		calculeaza suma dintre valorile scoase
		pune rezultatul obtinut in stiva

-> multiplication:	efectueaza doua pop-uri
			calculeaza produsul dintre valorile scoase
			pune rezultatul obtinut in stiva

-> division:	efectueaza doua pop-uri
		calculeaza catul dintre valorile scoase
 		pune rezultatul obtinut in stiva

-> space:	in momentul in care intalnim caracterul ' ' facem push
		la numarul retinut in registrul edx

-> push_element:	face push la numarul retinut in registrul edx

-> exit:	face pop-ul final (in stiva a ramas doar un singur
		element, adica rezultatul expresiei in forma postfixata) si il afiseaza
