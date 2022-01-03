#lang racket

(define empty-stream '())
(define-syntax stream-cons
  (syntax-rules ()
    ((_ term rest)
     (cons term (λ () rest)))))

(define stream-first car)
(define stream-rest (λ (s) ((cdr s))))
(define stream-empty? null?)

(define (stream-zip-with f . argstreams)
  (if (stream-empty? (car argstreams))
      empty-stream
      (stream-cons (apply f (map stream-first argstreams))
                   (apply stream-zip-with (cons f (map stream-rest argstreams))))))

;---FUNCȚIE DE PRELUARE ÎNTR-O LISTĂ A N ELEMENTE DIN FLUX---
;-----------UTILĂ LA AFIȘAREA FLUXULUI-----------------------
(define (stream-take s n)
  (cond ((zero? n) '())
        ((stream-empty? s) '())
        (else (cons (stream-first s)
                    (stream-take (stream-rest s) (- n 1))))))

;---FIBONACCI---
(define fibonacci-
  (stream-cons 0
               (stream-cons 1
                            (stream-zip-with +
                                             fibonacci-
                                             (stream-rest fibonacci-)))))
fibonacci-
(drop (stream-take fibonacci- 30) 29)






