#lang racket
(define (plus-curry x)
  (λ (y)
    (+ x y)))

(define (plus-uncurry x y)
  (+ x y))

(define inc1 (plus-curry 1))
;(inc1 10)
(define (inc2 y) (plus-uncurry 1 y))
;(inc2 10)

(define (ins-sort op)
  (λ (L)
    (if (null? L)
        L
        (ins op (car L) ((ins-sort op) (cdr L))))))

(define (ins op x L)
  (cond ((null? L) (list x))
        ((op x (car L)) (cons x L))
        (else (cons (car L) (ins op x (cdr L))))))

(define sort< (ins-sort <))
(define sort> (ins-sort >))
;(sort< '(5 2 7 4 1 3 2 6 3 7))
;(sort> '(5 2 7 4 1 3 2 6 3 7))

(define (selective-map p)
  (λ (f L)
    (cond ((null? L) L)
          ((p (car L)) (cons (f (car L)) ((selective-map p) f (cdr L))))
          (else (cons (car L) ((selective-map p) f (cdr L)))))))
(define map-on-evens (selective-map even?))
(define map-on-odds (selective-map odd?))
;(map-on-evens inc1 '(1 2 3 4 5))
;(map-on-odds inc1 '(1 2 3 4 5))

(define (add-range a b)
  (if (> a b)
      0
      (+ a (add-range (add1 a) b))))
;(add-range 5 10)

(define (fact n) (if (zero? n) 1 (* n (fact (- n 1)))))
(define (aprox-e lim)
  (define (iter i)
    (if (> i lim)
        0
        (+ (/ 1. (fact i))
           (iter (add1 i)))))
  (iter 0))
;(aprox-e 100)

(define (aprox-pi lim)
  (define (iter i)
    (if (> i lim)
        0
        (+ (/ 1. (sqr i))
           (iter (+ i 2)))))
  (iter 1))
;(sqrt (* 8 (aprox-pi 1000000)))

(define (series-sum start stop f next)
  (if (> start stop)
      0
      (+ (f start)
         (series-sum (next start) stop f next))))
(define (ex1 a b) (series-sum a b (λ (x) x) add1))
(define (ex2 lim) (series-sum 0 lim (λ (x) (/ 1. (fact x))) add1))
(define (ex3 lim) (series-sum 1 lim (λ (x) (/ 1. (sqr x))) (λ (x) (+ x 2))))
;(ex1 5 10)
;(ex2 100)
;(sqrt (* 8 (ex3 1000000)))

(define (maxL L M)
  (if (null? L)
      M
      (maxL (cdr L) (max M (car L)))))
;(maxL '(2 4 1 5 3 7 4 2) -inf.0)
;(foldl max -inf.0 '(2 4 1 5 3 7 4 2))
;(foldl + 0 (range 1 6))

(define (sqrL L)
  (if (null? L)
      L
      (cons (sqr (car L)) (sqrL (cdr L)))))
;(sqrL '(1 2 3 4 5))
;(map sqr '(1 2 3 4 5))

(define (initials names)
  (if (null? names)
      '()
      (cons (substring (car names) 0 1)
            (initials (cdr names)))))
;(initials '("John" "Winston" "Lennon"))
;(map (λ (name) (substring name 0 1)) '("John" "Winston" "Lennon"))

(define (pronouns words)
  (if (null? words)
      '()
      (if (member (car words) '("I" "you" "he" "she" "we" "they"))
          (cons (car words) (pronouns (cdr words)))
          (pronouns (cdr words)))))
;(pronouns '("I" "think" "you" "are" "how" "they" "said"))

(define (less-than n L)
  (if (null? L)
      '()
      (if (< (car L) n)
          (cons (car L) (less-than n (cdr L)))
          (less-than n (cdr L)))))
;(less-than 6 '(1 2 3 4 5 6 7 1 4))
(define (lt n L)
  (filter (λ (x) (< x n)) L))
;(lt 6 '(1 2 3 4 5 6 7 1 4))
;(map random (range 2 7))
(define (my-map f L)
  (foldr (λ (x acc) (cons (f x) acc))
         '()
         L))
;(my-map sqr '(1 2 3 4 5))
(define (my-filter p L)
  (foldr (λ (x acc) (if (p x) (cons x acc) acc))
         '()
         L))
;(my-filter odd? '(1 2 3 4 5 6 7 8 1 1))

;----------------ABSTRACTIZARE LA NIVEL DE DATE------------------        
;Constructori
;        empty-bst : -> BST
(define empty-bst '())
;        make-bst : BST x Elem x BST -> BST
(define (make-bst left root right)
  (list left root right))
;Operatori
;        left : BST -> BST
(define left first)
;        right : BST -> BST
(define right third)
;        key : BST -> Elem
(define key second)
;        empty-bst? : BST -> Bool
(define empty-bst? null?)
;        insert-bst : Elem x BST -> BST
(define (insert-bst x bst)
  (cond ((empty-bst? bst) (make-bst empty-bst x empty-bst))
        ((< x (key bst)) (make-bst (insert-bst x (left bst)) (key bst) (right bst)))
        (else (make-bst (left bst) (key bst) (insert-bst x (right bst))))))
;        list->bst : List -> BST
(define (list->bst L)
  (foldl insert-bst empty-bst L))

;(list->bst '(6 1 3 8 2))
