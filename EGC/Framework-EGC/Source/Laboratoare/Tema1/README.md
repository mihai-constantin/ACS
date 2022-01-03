### CONSTANTIN MIHAI - 336CA

# TEMA 1 - EGC - Flappy Bird

In cadrul temei am implementat propria versiune a jocului FlappyBird.

## Pasarea
Pasarea este formata din doua cercuri reprezentand corpul si capul pasarii,
un cerc pentru ochi, si 3 triunghiuri pentru aripi, respectiv cioc.
Pasarea este afectata de gravitatie. Ea are intotdeauna tendinta de a se 
inclina in jos si sa cada.

## Mediul in care se deplaseaza pasarea
Mediul inconjurator este creat din perechi de dreptunghiuri, de aceeasi latime,
dar de inaltimi diferite, unul ancorat sus, si celalalt ancorat jos. Inaltimea
dreptunghiurilor este stabilita aleator, respectand regula ca distanta dintre
doua perechi de dreptunghiuri sa fie suficient de mare, astfel incat pasarea
sa poata trece printre ele.

### Componente
1. pamant
2. iarba de culoare verde inchis, respectiv verde deschis, reprezentata sub
   forma de paralelograme ce se translateaza incontinuu pe axa Ox
3. norii, formati din cercuri suprapuse de culoare alba

## Utilizare optima a resurselor
In functia Init() se creeaza doua dreptunghiuri (unul pentru obstacolul de sus,
celalalt pentru obstacolul de jos), ce se translateaza incontinuu pe axa Ox.
Similar, exista doua paralelograme ce reprezinta iarba, unul pentru verde
inchis, celalalt pentru verde deschis.

## Gameplay
La rulare, se asteapta apasarea tastei SPACE, comportament indicat de mesajul
afisat pe ecran. In momentul in care se apasa tasta SPACE pentru prima data, 
jocul va incepe. Acesta se termina atunci cand pasarea moare (se loveste de
pamant sau de unul dintre obstacole).
Daca se apasa tasta SPACE, pasarea se va ridica, inclinandu-se in sus.
Pe masura ce timpul de supravietuire al pasarii creste, scorul jucatorului
se incrementeaza. Scorul curent reprezinta numarul de obstacole depasite 
la orice moment de timp. In momentul in care pasarea moare, in consola se va 
afisa scorul final al jucatorului, impreuna cu un mesaj.

## Coliziuni
Pentru realizarea coliziunilor dintre pasare si obstacole, respectiv dintre
pasare si pamant, am utilizat resursa de mai jos:
https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection
Am incadrat pasarea intr-un cerc si am verificat daca exista coliziune cu
dreptunghiul respectiv.

## Bonus
1. Animatie de scalare pentru perechile de dreptunghiuri. In momentul in care
scorul jucatorului devine 10, obstacolele se pot comporta precum un set de usi
glisante de la un lift modern, astfel incat sa se apropie si sa se departeze
incontinuu, pastrand totusi o distanta suficient de mare intre ele astfel incat
pasarea sa treaca printre ele.
2. Dificultatea jocului creste pe masura ce creste scorul jucatorului.
3. Animatie care sa simuleze modul prin care pasarea da din aripi.