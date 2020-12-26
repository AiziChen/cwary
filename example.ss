(@add '("/" "/home") home)
(define home
  (lambda (req)
    (response 200 "text/plain"
      (string-append "hello, world" (s-ref req 'query)))))


;; `@..` -- an web procedure/annotation
(@server "8080")

