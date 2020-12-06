;; Load the `cwary` C dynamic library
(case (machine-type)
  [(i3le ti3le a6le ta6le)
   (load-shared-object "./lib/clib/libcwary.so")]
  [(i3osx ti3osx a6osx ta6osx)
   (load-shared-object "./lib/clib/libcwary.dylib")])

(load "lib/SObj.scm")
(load "lib/tree-map.ss")
(load "lib/c-extra/libc-extra.ss")

(define check
  (lambda (who x)
    (if (< x 0)
	(error who (c-error))
	x)))

(define starts-with
  (lambda (l1 l2)
    (cond
     [(null? l1) (null? l2)]
     [(null? l2) #t]
     [else
      (and (eq? (car l1) (car l2))
	   (starts-with (cdr l1) (cdr l2)))])))

(define starts-with-bvu8
  (case-lambda
    [(bv ls)
     (starts-with-bvu8 bv ls 0)]
    [(bv ls n)
     (cond
      [(= n (bytevector-length bv))
       (null? ls)]
      [(null? ls) #t]
      [else
       (and (eq? (bytevector-u8-ref bv n) (car ls))
	    (starts-with-bvu8 bv1 (cdr ls) (1+ n)))])]))

