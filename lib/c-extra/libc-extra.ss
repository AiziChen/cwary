(load-shared-object "lib/c-extra/libc-extra.dylib")

(define c-error
  (foreign-procedure "get_error"
		     () string))
