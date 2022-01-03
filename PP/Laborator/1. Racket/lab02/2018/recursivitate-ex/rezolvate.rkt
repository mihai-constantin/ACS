#lang racket

;; DrRacket pune la dispozitie o functie de tracing.
(require (lib "trace.ss"))

;; Exercitiul 1 - folosirea functiei trace pentru a intelege mai bine desfasurarea recursivitatii

(define (factorial n)
  (if (= n 1)
      1
      (* n (factorial (- n 1)))))

;; Acum putem observa direct cum arata executia functiei factorial:
;(trace factorial)
;(factorial 5)

;; Ce trebuie retinut in memoria programului la un moment dat:
;; - argumentul n curent (de ex 1)
;; - un numar x de operatii care trebuie efectuate pe revenire (de ex inmultirea cu 2, inmultirea cu 3 etc)
;;
;; - avansul in recursivitate are loc de O(n) ori, cand se si depun informatii pe stiva, avand un volum O(n)
;; - calculul propriu-zis se desfasoara pe revenirea din recursivitate, cand se efectueaza O(n) operatii
;; - mai dureaza si inmultirile ceva, fiind vorba de numere mari
;; - fiecare nivel de recursivitate asteapta ca problema sa se intoarca din nou la el,
;;   ca sa ajusteze rezultatul asa cum numai el stie!

;; Rulati aceasta functie factorial pe numere din ce in ce mai mari.
;; Observati durata de rulare.
;(time (factorial 10000))

(define (factorial2 n) ;; acest apel produce redefinirea functiei factorial
  (fact-iter 1 1 n))

(define (fact-iter product counter max-count)
  (if (> counter max-count)
      product
      (fact-iter (* counter product)
                 (+ counter 1)
                 max-count)))

;; Acum putem observa direct cum arata executia functiei factorial iterativ.
;(trace fact-iter)
;(factorial2 100)

;; Ce trebuie retinut in memoria programului la un moment dat:
;; - argumentul n, argumentul n curent si rezultatul partial (de ex 1, 6)
;; - nimic altceva
;;
;; - avansul in recursivitate are loc de O(n) ori, cand are loc si calculul propriu-zis
;; - nu se efectueaza operatii pe revenirea din recursivitate
;; - ca si mai sus, o parte din timpul rulare e dedicata inmultirii de numere mari
;; - un anumit nivel de recursivitate se intalneste o sg data cu problema, 
;;   o da mai departe in forma simplificata si poate uita de ea imediat!
;; - de aceea aceasta forma de recursivitate se numeste "pe coada" - 
;;   pt ca apelul recursiv este ultimul lucru care se intampla (este la coada)

;; Rulati aceasta functie factorial pe numere din ce in ce mai mari.
;; Observati durata de rulare.
;(time (factorial 10000))

;; Exercitiul 2 - acelasi lucru pentru functia fibonacci

(define (fib n)
  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (+ (fib (- n 1))
                 (fib (- n 2))))))

;(trace fib)
;(fib 5)

;; - in program se retine calea de revenire (pe stiva) si pentru
;;   apelul curent se retin n si cele 2 rezultate partiale
;;   de la fib apelat cu (n-1) si (n-2)
;; - numarul de apeluri recursive este 2 din fiecare fib unde n >= 2
;;   iar per total este 2 * (valoarea_returnata) - 1.  Asta se deduce
;;   observand ca pe cel mai jos nivel valorile de adunat sunt toate "1",
;;   iar cand fib nu intoarce 1 direct, efectueaza o adunare.  Pentru
;;   a aduna un sir de K elemente doua cate doua, e nevoie de K-1 operatii
;;   de adunare.  Cum toate valorile "sirului" initial sunt 1, e clar ca 
;;   numarul K este egal cu suma finala, si deci vor fi K apeluri din care
;;   avem rezultat direct 1, si K-1 apeluri care vor face sume pe revenire,
;;   deci total 2K-1, cu K = (fib n).
;; - operatii pe revenirea din recursivitate:  1 la fiecare fib
;;   neterminal in arbore (adunarea), si (fib n)-1 in total.

(define (fib2 n)
  (fib-iter 1 0 n))

(define (fib-iter a b count)
  (if (= count 0)
      b
      (fib-iter (+ a b) a (- count 1))))

;(trace fib-iter)
;(fib2 5)

;; Varianta iterativa are O(n) timp, si O(1) spatiu
;; Varianta recursiva are O(fib n) timp, si O(n) spatiu
;; Atat la spatiu cat si la timp varianta recursiva este mai ineficienta,
;; mai ales in privinta timpului, avand in vedere ca (fib n) este exponential in n.

;; Exercitiul 3 - suma elementelor unei liste - varianta iterativa

(define (sum-list L)
  (sum-list-iter 0 L))

(define (sum-list-iter sum L)
  (if (null? L)
      sum
      (sum-list-iter (+ sum (car L)) (cdr L))))

;(trace sum-list-iter)
;(sum-list '(1 2 3 4 5))
  
;; Explicatie: pornesc din starea "mai am de adunat elementele din toata lista"
;; si "pana acum am adunat nimic", si iau cate un element de la
;; inceputul partii ramase, si il adun la ce am adunat pana acum.
;; Cand nu mai am nimic ramas de prelucrat, inseamna ca am acumulat
;; toata suma in variabila sum si pot sa intorc rezultatul final.

;; Exercitiul 4 - lungimea unei liste - varianta iterativa

(define (len L)
  (len-iter 0 L))

(define (len-iter result L)
  (if (null? L)
      result
      (len-iter (+ 1 result) (cdr L))))

;(trace len-iter)
;(len '(1 a 2 b 3 c 4 d 5 e))

;; Exercitiul 5 - append intre 2 liste - varianta iterativa

(define (app A B)
  (app-iter B (reverse A)))

(define (app-iter B Result)
  (if (null? B)
      (reverse Result)
      (app-iter (cdr B) (cons (car B) Result))))

(trace app-iter)
(app '(1 2 3 4 5) '(a b c))

;; O problema comuna a solutiilor recursive pe coada este ca
;; rezultatul este construit in ordinea gresita. Se intampla din cauza
;; ca folosim cons drept constructor de liste, care adauga doar la
;; inceput. Solutia uzuala este folosirea functiei reverse
;; pentru inversarea rezultatului inainte de return.