(load "lib/web/libweb.ss")

(define bytevector->string-with-none-eol-style
  (lambda (s)
    (let ([tx (make-transcoder
	       (utf-8-codec)
	       (eol-style none)
	       (error-handling-mode raise))])
      (string->bytevector s tx))))






