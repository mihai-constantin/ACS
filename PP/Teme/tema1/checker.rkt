#lang racket

; ignorați următoarele linii de cod.
(define show-defaults 200) ; câte exerciții la care s-au întors rezultate default să fie arătate detaliat
(define prepend #t) (define name-ex '(testul . testele)) ; variante: '(exercițiul . exercițiile) sau '(testul . testele) sau '(task . taskurile)
(define default-results '(#f 0 () your-code-here)) ; ce rezultate default sunt întoarse în exerciții
(define (default-result r) (set! default-results (cons r default-results)))
(define : 'separator) (define punct 'string) (define puncte 'string) (define BONUS 'string) (define total 0) (define all '()) (define n-ex 0) (define p-ex 0) (define defaults '())
(define (ex n sep p . s) (set! n-ex n) (set! p-ex p) (set! all (cons (list n p) all))) (define testul ex) (define (p L) (map (λ (e) (display e) (display " ")) L) (newline))
(define (expart per part) (if (< per 1) (string-append (number->string n-ex) (symbol->string part)) n-ex))
(define (whengood expart per) (let ((pts (* p-ex per))) (and (if prepend (printf "+~v: " pts) (printf "OK: ")) (p `(,(car name-ex) ,expart rezolvat: + ,pts ,(if (= pts 1) 'punct 'puncte))) (set! total (+ total pts)))))
(define (whenbad expart gvn expcd) (and (when (member gvn default-results) (set! defaults (cons expart defaults))) (when (or (not (member gvn default-results)) (<= (length defaults) show-defaults)) (bad-res expart gvn expcd))))
(define (bad-res expart gvn expcd . c) (p (append `(NU: la ,(car name-ex) ,expart rezultatul ,gvn) (if (null? c) `(diferă de cel așteptat: ,expcd) c))))
(define (check-cond part per gvn tests) (let ((r ((car tests) gvn))) (if (eq? r #t) (apply check-exp-cond part per gvn (cdr tests)) (bad-res (expart per part) gvn #f (or r "nu îndeplinește condiția")))))
(define (check-exp given expected) (check-exp-part "" 1 given expected))
(define (check-exp-part part per gvn expcd) (let ((expart (expart per part))) (if (equal? gvn expcd) (whengood expart per) (whenbad expart gvn expcd))))
(define (check-exp-cond part per gvn . tests) (if (member gvn default-results) (whenbad (expart per part) gvn (last tests)) (if (null? (cddr tests)) (check-exp-part part per ((car tests) gvn) (cadr tests)) (check-cond part per gvn tests))))
(define (sumar) (when (and (not (null? defaults)) (< show-defaults (length defaults))) (p `(... rezultatul implicit dat la ,(cdr name-ex) ,(reverse defaults)))) (p `(total: ,total puncte)))
(define (mark-helper) (printf "---~nEx  puncte    Total până aici~n") (foldr (λ (e-p t) (p `(,(car e-p) : ,(cadr e-p) puncte. total 1 - ,(car e-p) : ,(+ t (cadr e-p)))) (+ t (cadr e-p))) 0 all))

(require "stack-machine.rkt")

(testul 0 : 20 puncte)
(when (not (equal? (make-stack) 'your-code-here))
  (check-exp-part 'a (/ 1. 10) (make-stack) empty-stack))
(check-exp-part 'b (/ 1. 10) (top (push 2 (make-stack))) 2)
(check-exp-part 'c (/ 1. 10) (pop (push 2 (make-stack))) empty-stack)
(check-exp-part 'd (/ 1. 10) (top (push 3 (push 2 (make-stack)))) 3)
(check-exp-part 'e (/ 1. 10) (top (get-stack (make-stack-machine (pop (push 3 (push 2 (make-stack)))) 'None 'None 'None 'None 'None))) 2)
(check-exp-part 'f (/ 1. 10) (get-varnames (make-stack-machine 'None (hash 0 'None 1 'None) 'None 'None 'None 'None)) (hash 0 'None 1 'None))
(check-exp-part 'g (/ 1. 10) (get-consts (make-stack-machine 'None 'None (hash 0 0 1 1 2 2) 'None 'None 'None)) (hash 0 0 1 1 2 2))
(check-exp-part 'h (/ 1. 10) (get-names (make-stack-machine 'None 'None 'None (hash 0 "prod") 'None 'None)) (hash 0 "prod"))
(check-exp-part 'i (/ 1. 10) (get-code (make-stack-machine 'None 'None 'None 'None '(100 1 125 0 120 24 116 0 100 2 131 1 68 0 93 12 125 1 124 0 100 2 55 0 125 0 113 14 87 0 100 0 83 0) 'None)) '(100 1 125 0 120 24 116 0 100 2 131 1 68 0 93 12 125 1 124 0 100 2 55 0 125 0 113 14 87 0 100 0 83 0))
(check-exp-part 'j (/ 1. 10) (get-IC (make-stack-machine 'None 'None 'None 'None 'None 2)) 2)

(sumar)
