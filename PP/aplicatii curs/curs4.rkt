;---------------EFECTE LATERALE--------------------
;(define counter 1)
;
;(define (display-and-inc-counter)
;  (display counter)
;  (set! counter (add1 counter)))
;
;(display-and-inc-counter)
;(newline)
;(display-and-inc-counter)

;(define a (λ () n))
;(define n 5)
;(a)


;---------------LEGARE DINAMICĂ--------------------
;(define (f)
;  (g 5))
;
;(define (g x)
;  (* x x))
;(f)
;
;(define (g x)
;  (* x x x))
;(f)

;-------------------LAMBDA-------------------------
;(define test
;  (λ (x y z)
;    (display x)
;    (if (< y 4)
;        (test (add1 y) z z))
;    z))
;
;(test 1 2 4)

;------------------LET-URI-------------------------
;(define x 2) ; să se încerce și cu linia asta comentată
;(let ((x 5) (y (add1 x)))
;  (cons x y))
;
;(let* ((x (add1 x)) (y (add1 x)) (z (+ x y)))
;  (list x y z))
;
;(letrec ((par? (λ (n) 
;                 (if (zero? n)
;                     #t
;                     (impar? (sub1 n)))))
;         (impar? (λ (n)
;                   (if (zero? n)
;                       #f
;                       (par? (sub1 n))))))
;  (par? 24))
;
;(letrec ((x y) (y 1)) x)

;(define inversare
;  (lambda (nr)
;    (let invers ((crt nr) (inv 0))
;      (if (zero? crt)
;	  inv
;	  (let ((cat (quotient crt 10))
;		(rest (modulo crt 10)))
;	    (invers cat (+ (* inv 10) rest)))))))
;(inversare 5123)

;----------------AVANTAJE DEFINE-------------------
;(define par? (λ (n) 
;                 (if (zero? n)
;                     #t
;                     (impar? (sub1 n)))))
;
;(define impar? (λ (n) 
;                 (if (zero? n)
;                     #f
;                     (par? (sub1 n)))))
;
;(impar? 5)

;-------------CONTEXT COMPUTAȚIONAL----------------
;(define a 1)
;(define (f x)
;  (+ x
;     (let ((x 5))
;       (* a x))))
;(f 2)
;(define a 2)
;(f 2)


;(define (fact n)
;  (if (zero? n)
;      1
;      (* n (fact (- n 1)))))
;(define g fact)
;(g 4)
;
;(define (fact n) n)
;(g 4)

;(define (g x)
;  (* x x))
;(define f
;  (g 5))
;f
;
;(define (g x)
;  (* x x x))
;f

;---------------REZOLVARE TEST------------------
(define (f L)
  (even? (length (filter odd? L))))
;(f '(1 2 3 4 5))
;(f '(1 2 3 1 5))

(define (g1 L)
  (apply append (map (λ (x) (list x x)) (filter even? L))))
;(g1 '(1 2 3 4 5))
;(g1 '(1 2 6 3 4 5))
;; SAU
(define (g2 L)
  (foldr (λ (x acc) (append (list x x) acc)) '() (filter even? L)))
;(g2 '(1 2 3 4 5))
;(g2 '(1 2 6 3 4 5))
