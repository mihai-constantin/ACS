;; CONSTANTIN MIHAI - 321CD

#lang racket
(require "opcodes.rkt")
(provide make-stack-machine)
(provide run-stack-machine)
(provide get-stack)
(provide get-varnames)
(provide get-consts)
(provide get-names)
(provide get-code)
(provide get-IC)
(provide empty-stack)
(provide make-stack)
(provide push)
(provide pop)
(provide top)

;; TODO 1:
;; Alegeți metoda de reprezentarea a unei stive.

;; Stiva reprezentata sub forma unei liste
(define empty-stack
  '())

;; Creare stiva vida
(define (make-stack)
  empty-stack)

;; Operatia de push pe stiva - intoarce stiva dupa push
(define (push element stack)
  (cons element stack))

;; Operatia de pop pe stiva - intoarce stiva dupa pop
(define (pop stack)
  (cdr stack))

;; Primul element din stiva (TOS)
(define (top stack)
  (car stack))

;; Al doilea element din stiva (TOS1)
(define (top1 stack)
  (car (cdr stack)))

;; TODO 2:
;; Alegeți metoda de reprezentare a unei mașini stivă.
;; Definiți make-stack-machine, acesta trebuie sa primeasca cele 4 segmente de date
;; Veți avea nevoie de o stivă pentru execuție și un counter ca să stiți
;; la ce instrucțiune sunteți.
(define (make-stack-machine stack co-varnames co-consts co-names co-code IC)
  (list stack co-varnames co-consts co-names co-code IC))

;; Definiți funcțiile `get-varnames`, `get-consts`, `get-names`,
;; `get-code`, `get-stack`, `get-IC` care primesc o mașina stivă și întorc
;; componenta respectivă

;; ex:
;; > (get-varnames (make-stack-machine empty-stack 'dummy-co-varnames (hash) (hash) (list) 0))
;; 'dummy-co-varnames
(define (get-varnames stack-machine)
  (car (cdr stack-machine)))

;; ex:
;; > (get-consts (make-stack-machine empty-stack (hash) 'dummy-co-consts (hash) (list) 0))
;; 'dummy-co-consts
(define (get-consts stack-machine)
  (car (cdr (cdr stack-machine))))

;; ex:
;; > (get-names (make-stack-machine empty-stack (hash) (hash) 'dummy-co-names (list) 0))
;; 'dummy-co-names
(define (get-names stack-machine)
  (car (drop stack-machine 3)))

;; ex:
;; > (get-code (make-stack-machine empty-stack (hash) (hash) (hash) 'dummy-co-code 0))
;; dummy-co-code
(define (get-code stack-machine)
  (car (drop stack-machine 4)))

;; Întoarce stiva de execuție.
;; ex:
;; > (get-code (make-stack-machine 'dummy-exec-stack (hash) (hash) (hash) (list) 0))
;; dummy-exec-stack
(define (get-stack stack-machine)
  (car stack-machine))

;; Întoarce instruction counterul.
;; ex:
;; > (get-code (make-stack-machine empty-stack (hash) (hash) (hash) (list) 0))
;; 0
(define (get-IC stack-machine)
  (car (drop stack-machine 5)))

(define symbols (list 'STACK 'CO-VARNAMES 'CO-CONSTS 'CO-NAMES 'CO-CODE 'INSTRUCTION-COUNTER))

;; TODO 3:
;; Definiți funcția get-symbol-index care gasește index-ul simbolului in listă.
(define (get-symbol-index symbol)
  (let iter [(mylist symbols) (idx 1)]
    (if (equal? (car mylist) symbol)
        idx
        (iter (cdr mylist) (add1 idx)))))

;; Definiți funcția update-stack-machine care intoarce o noua mașina stivă
;; înlocuind componenta corespondentă simbolului cu item-ul dat în paremetri.
;; > (get-varnames (update-stack-machine "new-varnames" 'CO-VARNAMES stack-machine))
;; "new-varnames"
;; > (get-varnames (update-stack-machine "new-names" 'CO-NAMES stack-machine))
;; "new-names"
(define (update-stack-machine item symbol stack-machine)
  (append (take stack-machine (sub1 (get-symbol-index symbol))) (list item) (drop stack-machine (get-symbol-index symbol))))

;; Definiți funcția push-exec-stack care primește o masină stivă și o valoare
;; și intoarce o noua mașina unde valoarea este pusă pe stiva de execuție
(define (push-exec-stack value stack-machine)
  (make-stack-machine (push value (get-stack stack-machine)) (get-varnames stack-machine) (get-consts stack-machine) (get-names stack-machine) (get-code stack-machine) (get-IC stack-machine)))

;;  Definiți funcția pop-exec-stack care primește o masină stivă
;;  și intoarce o noua mașina aplicând pop pe stiva de execuție.
(define (pop-exec-stack stack-machine)
  (make-stack-machine (pop (get-stack stack-machine)) (get-varnames stack-machine) (get-consts stack-machine) (get-names stack-machine) (get-code stack-machine) (get-IC stack-machine)))

;; TODO 4:
;; Definiți funcția run-stack-machine care execută operații pană epuizează co-code.
(define (run-stack-machine stack-machine)
  (let iter [(new-stack-machine stack-machine) (co-code (get-code stack-machine)) (ic (get-IC stack-machine))]
    (define instruction-code
      (list-ref (list-ref co-code ic) 0))
    (cond
      ((equal? instruction-code 'LOAD_CONST)
       (iter (push-exec-stack (hash-ref (get-consts new-stack-machine) (cdr (list-ref co-code ic))) new-stack-machine) co-code (add1 ic)))
          
      ((equal? instruction-code 'STORE_FAST)
       (iter (pop-exec-stack (update-stack-machine (hash-set (get-varnames new-stack-machine) (cdr (list-ref co-code ic)) (top (get-stack new-stack-machine))) 'CO-VARNAMES new-stack-machine))
             co-code (add1 ic)))
          
      ((equal? instruction-code 'LOAD_FAST)
       (iter (push-exec-stack (hash-ref (get-varnames new-stack-machine) (cdr (list-ref co-code ic))) new-stack-machine) co-code (add1 ic)))

      ((or (equal? instruction-code 'BINARY_ADD) (equal? instruction-code 'INPLACE_ADD))
       (iter (push-exec-stack (+ (top (get-stack new-stack-machine)) (top1 (get-stack new-stack-machine))) (pop-exec-stack (pop-exec-stack new-stack-machine))) co-code (add1 ic)))
           
      ((or (equal? instruction-code 'BINARY_SUBTRACT) (equal? instruction-code 'INPLACE_SUBTRACT))
       (iter (push-exec-stack (- (top1 (get-stack new-stack-machine)) (top (get-stack new-stack-machine))) (pop-exec-stack (pop-exec-stack new-stack-machine))) co-code (add1 ic)))
          
      ((or (equal? instruction-code 'BINARY_MODULO) (equal? instruction-code 'INPLACE_MODULO)) 
       (iter (push-exec-stack (modulo (top1 (get-stack new-stack-machine)) (top (get-stack new-stack-machine))) (pop-exec-stack (pop-exec-stack new-stack-machine))) co-code (add1 ic)))

      ((equal? instruction-code 'COMPARE_OP)
       (iter (push-exec-stack ((get-cmpop (cdr (list-ref co-code ic))) (top1 (get-stack new-stack-machine)) (top (get-stack new-stack-machine))) (pop-exec-stack (pop-exec-stack new-stack-machine)))
             co-code (add1 ic)))
           
      ((equal? instruction-code 'POP_JUMP_IF_FALSE)
       (if (top (get-stack new-stack-machine))
           (iter (pop-exec-stack new-stack-machine) co-code (add1 ic))
           (iter (pop-exec-stack new-stack-machine) co-code (/ (cdr (list-ref co-code ic)) 2))))
           
      ((equal? instruction-code 'POP_JUMP_IF_TRUE)
       (if (top (get-stack new-stack-machine))
           (iter (pop-exec-stack new-stack-machine) co-code (/ (cdr (list-ref co-code ic)) 2))
           (iter (pop-exec-stack new-stack-machine) co-code (add1 ic))))
           
      ((equal? instruction-code 'JUMP_ABSOLUTE)
       (iter new-stack-machine co-code (/ (cdr (list-ref co-code ic)) 2)))

      ((equal? instruction-code 'FOR_ITER)
       (if (null? (top (get-stack new-stack-machine)))
           (iter (pop-exec-stack new-stack-machine) co-code (+ (add1 (/ (cdr (list-ref co-code ic)) 2)) ic))
           (iter (push-exec-stack (car (top (get-stack new-stack-machine))) (push-exec-stack (cdr (top (get-stack new-stack-machine))) (pop-exec-stack new-stack-machine))) co-code (add1 ic))))

      ((equal? instruction-code 'LOAD_GLOBAL)
       (iter (push-exec-stack (hash-ref (get-names new-stack-machine) (cdr (list-ref co-code ic))) new-stack-machine) co-code (add1 ic)))

      ((equal? instruction-code 'CALL_FUNCTION)
       ;; my-argv-bonus - o lista formata din lista de argumente pentru functia ce se afla in varful stivei si noua stack-machine dupa eliminarea celor n argumente de pe stiva
       (define my-argv-bonus (let argv-iter [(nr-argv (cdr (list-ref co-code ic))) (new-stack-machine-bonus new-stack-machine) (my-argv '())]
                               (if (zero? nr-argv)
                                   (list my-argv new-stack-machine-bonus)
                                   (argv-iter (sub1 nr-argv) (pop-exec-stack new-stack-machine-bonus) (cons (top (get-stack new-stack-machine-bonus)) my-argv)))))
       ;; lista de argumente
       (define my-list-bonus
         (car my-argv-bonus))
       ;; noua stack-machine
       (define my-stack-machine-bonus
         (car (cdr my-argv-bonus)))
       ;; aplic functia pe cele n argumente, elimin functia de pe stiva si dau push la rezultat
       (iter (push-exec-stack (apply (get-function (top (get-stack my-stack-machine-bonus))) my-list-bonus) (pop-exec-stack my-stack-machine-bonus)) co-code (add1 ic)))

      ((equal? instruction-code 'POP_TOP)
       (iter (pop-exec-stack new-stack-machine) co-code (add1 ic)))
          
      ((equal? instruction-code 'RETURN_VALUE)
       new-stack-machine)
          
      (else (iter new-stack-machine co-code (add1 ic))))))

