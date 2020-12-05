(define c-error
  (foreign-procedure "get_error"
		     () string))
(define get-string
  (foreign-procedure "get_string"
		     (void*)
		     string))


