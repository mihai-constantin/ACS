# Laborator 5 - Tehnici de Optimizare de Cod – Inmultirea Matricelor

## Varianta clasica

Inmultire de matrici in O(n^3).

Rezultatul pentru n = 1500 este redat mai jos:
$ ./clasic
Time: 26.224809 s

## Varianta pointeri
Se observa o prima imbunatatire in situatia cand inlocuim constantele 
cu pointeri

$ ./const_elim
Time: 22.312633 s

## Ordinea buclelor

Rezultatul pentru o ordonare k-i-j este redat mai jos (imbunatatire evidenta):
$ ./loop_reorder_better
Time: 9.077069 s

Rezultatul pentru o ordonare k-j-i este redat mai jos (performanta 
foarte scazuta):
$ ./loop_reorder_worse
Time: 35.936051 s

## Inmultire folosind blocuri
Matrici liniarizate

$ ./block_lin 1500 25 1
Multiply matrices 1 times...
Time = 16.331519 

## Bonus
Varianta clasica (matrici alocate ca vectori de vectori)

$ ./block_classic 1500 25 1
Multiply matrices 1 times...
Time = 18.001953 s
