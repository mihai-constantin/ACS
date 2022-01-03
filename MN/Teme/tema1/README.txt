% CONSTANTIN MIHAI - 311CD

Tema 1 MN - PageRank

Cerinta 1 - Algoritmul Iterative

Am citit din fisierul de intrare numarul de noduri N, iar apoi lista de vecini, formand atat matricea de adiacenta A, cat si matricea diagonala K. 
In continuare, am atribuit valoarea 0 elementelor de pe diagonala principala din A. Daca A(i,i) == 1, K(i,i) s-a decrementat cu o unitate.
Am determinat cu ajutorul formulei matricea M, folosindu-ma de functia inv_diagonal(matrix) ce returneaza inversa unei matrice diagonale. 
Am initializat vectorul R cu 1/N, continuand algoritmul pana cand norm(R - R_0) < eps.
Functia Iterative returneaza valoarea R(t) - penultima estimare a vectorului R.

Cerinta 2 - Algoritmul Algebraic

Citirea s-a realizat ca mai sus. Pentru determinarea valorii vectorului R, am folosit formula din cerinta. 
Pentru a evita calculul inversei matricei (I - d * M), am folosit algoritmul Gram-Schmidt. 
Am rezolvat n sisteme de ecuatii de forma R * x_i = Q' * e_i, unde R este o matrice superior triunghiulara, Q este o matrice ortogonala (Q^(-1) = Q'), 
e_i este coloana i din matricea unitate I_n si x_i este vectorul solutie. 
Am determinat vectorul solutie x_i cu ajutorul functiei SST(matrix, b) care rezolva un sistem superior triunghiular.
Inversa va fi formata cu ajutorul vectorilor x_i : A^(-1) = [x_1 x_2 ... x_n].

Cerinta 3 - Gradul de Apartenenta

Am determinat prin calcul valorile pentru a si b, punand conditia ca functia sa fie continua: a = 1 / (val2 - val1); b = val1 / (val1 - val2). 
In continuare, am calculat valorea functiei membru in punctul x.
In fisierul PageRank.m am creat un fisier de iesire, al carui nume este dat de numele fisierului primit ca parametru, la care se concateneaza sirul .out.
Am afisat pe prima linie a fisierului numarul de noduri N si apoi vectorul PR, obtinut in urma algoritmilor Iterative si Algebraic.
Am sortat descrescator vectorul PR obtinut in urma algoritmului Algebraic cu ajutorul algoritmului insertion sort. De asemenea, am format un vector de
pozitii, asociat fiecarui element. Am afisat N linii de forma i j F, unde i reprezinta indici in vectorul PR, j reprezinta nodul al carui PageRank este PR(i),
iar F este valoarea functiei de apartenenta in punctul PR(i).


