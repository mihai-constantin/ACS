Re: Template latex pentru studenti (v3)

18 februarie 2017

Dragi studenti,

Pentru a incepe sa redactati rapoarte in LaTex, va recomand urmatoarele:

1) Cititi documentul README2_v2.pdf, accesand si link-urile indicate.
2) Instalati-va latex
3) Compilati fisierul main_referat.tex
In urma compilarii trebuie sa obtineti un fisier main_referat.pdf identic cu README2.pdf (pe care l-am pus in aceasta arhiva ca martor).

Nota/recomandari:

- Acest pachet de fisiere a fost testat pe Linux (Ubuntu) pe care a fost instalat latex astfel
====
sudo apt-get update
sudo apt-get install texlive-full
=== (dureaza ceva mai mult ca timp, dar aveti toate pachetele)
si
ca IDE TexStudio instalat astfel
============
sudo apt-get install texstudio
===========
Alternativ, puteti folosi make pentru compilare (vedeti fisierul Makefile din aceasta arhiva)

Pentru Windows, va recomand sa va instalati miktex (http://miktex.org/) si TeXnikCenter (http://www.texniccenter.org/) care este un IDE pentru dezvoltarea de documente in LaTeX; trebuie sa aveti instalat si ghostscript si ghostview. In TeXnikCenter, deschideti fisierul principal, creati un proiect (meniul Project => Create with active file as main file)  si bifati optiunea bibtex. Pentru compilare alegeti latex => ps => pdf


Daca intampinati dificultati, aveti intrebari sau sugestii de imbunatatire a oricarui fisier din aceasta arhiva, nu ezitati sa imi scrieti. 

OBS:
1) In documentul de mai sus figurile sunt in format eps si de aceea compilarea trebuie sa genereze pe rand formatele dvi, ps, pdf

2) Daca doriti sa includeti formate de tip jpeg, png, etc, atunci trebuie sa compilati astfel:
in Windows - alegeti dvi => pdf direct
in linux - folositi pdflatex  (dati comanda:  make -f Makefile2)


3) Pentru lucrul in linux, fisierele Makefile nu au inclus explicit toate dependintele de restul de fisiere. De aceea, daca ati modificat sau adaugat fisiere, inainte de comanda make stergeti fisierul main_referat.pdf. Puteti face asta cu comanda:  make cleanpdf 

Succes!

P.S. Aceasta noua versiune a machetei latex include desene de circuite. 

--------------------------------------
Prof. Gabriela Ciuprina
"Politehnica" University of Bucharest
Electrical Engineering Department
Numerical Methods Laboratory (EA-D)
Spl. Independentei 313,
060042, Bucharest, Romania
-----
email: gabriela@lmn.pub.ro
       gabriela.ciuprina@upb.ro
web  : http://www.lmn.pub.ro/~gabriela
--------------------------------------
