### CONSTANTIN MIHAI - 336CA

# TEMA 2 - EGC - Avion cu Motor

In cadrul temei am implementat un joc in care sunt un aviator ce se deplaseaza
in spatiul 3D, evitand obstacole (reprezentate de sfere rosii) si colectionand
combustibil (reprezentat de obiecte de tip teapot) sau vieti (sfere galbene).

## Avionul
Avionul a fost realizat din mai multe elemente:
1. corp principal (paralelipiped mai ingust spre coada si mai larg spre fata)
2. aripi, reprezentate de doua paralelipipede dreptunghice, dispuse de-a lungul
   corpului principal al avionului
3. coada avionului, reprezentata de un paralelipiped dreptunghic
4. suport de elice
5. elice - aceasta are o rotatie permamenta de-a lungul axei Ox

## Norii
Norii sunt formati din 4 cuburi de culori diferite, pozitionate aleator unul
langa altul. Norii au o rotatie permanenta in jurul marii. De asemenea, anumite
cuburi din componenta norilor au o miscare de rotatie proprie.

## Marea
Pentru constructia marii deasupra careia zboara avionul, am folosit un cilindru
cu centrul in origine. Forma neregulata a marii a fost realizata in 
VertexShader prin deformari aleatoare, dar care sa asigure o continuitate in
timp.

## Obstacole
Obstacolele sunt reprezentate de sfere de culoare rosie cu o rotatie continua
in jurul marii. De asemenea ele dispun de o rotatie proprie in jurul axei Oy.

## Combustibil
Combustibilul este evidentiat prin obiecte de tip teapot, 3 la numar, dispuse
intr-o insiruire arcuita. Acestea au o animatie de rotire permanenta.

In momentul coliziunii avionului cu obiecte de tip teapot sau sfera rosie, 
acestea din urma dispar, iar combustibilul avionului creste, respectiv numarul
de vieti scade cu o unitate.

## Interfata cu utilizatorul
Interfata cu utilizatorul este evidentiata prin afisarea numarului de vieti
ramase la orice moment de timp, cat si a combustibilului.
Afisarea acestor elemente s-a realizat cu ajutorul unor shadere.

## Bonusuri
Bonusurile implementate:
1. iluminare in fata avionului
2. constructia realista a avionului
3. cresterea dificultatii jocului pe masura trecerii timpului
4. crearea unor obiecte speciale (sfere galbene) ce aduc o viata in plus 
   avionului