#lang racket
(require 2htdp/batch-io)
(require "opcodes.rkt")
(require "stack-machine.rkt")

(define (split-by lst n)
  (if (empty? lst)
    '()
    (cons (take lst n) (split-by (drop lst n) n))))


(define (co-varnames varnames-list)
  (apply hash (flatten
              (build-list (length varnames-list)
              (lambda (x) (cons x 'None))))))

(define (co-consts consts-list)
  (make-hash (map (lambda (index x) (cons index x))
             (range (length consts-list))
             consts-list)))

(define (co-names names-list)
  (make-hash (map cons (range (length names-list)) names-list)))


(define (co-code code-list)
  (map (lambda (chunk)
    (cons (get-opname (car chunk)) (cadr chunk)))
    (split-by code-list 2)))

(define (parse-args args)
  (make-stack-machine
    empty-stack
    (co-varnames (car args))
    (co-consts (cadr args))
    (co-names (caddr args))
    (co-code (cadddr args))
    0))

(define arguments
  (let ((filename (vector-ref (current-command-line-arguments) 0)))
        (file->list filename)))

(let* ([var-result (get-varnames (run-stack-machine (parse-args arguments)))]
      [list-result (sort (hash->list var-result) #:key car <)]
      [port (open-output-file "byterun.log")])
      (writeln list-result port))
