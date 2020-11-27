(load "lib/SObj.scm")
(load "lib/tree-map.ss")
(load "lib/c-extra/libc-extra.ss")

(define check
  (lambda (who x)
    (if (< x 0)
	(error who (c-error))
	x)))
