(load-shared-object "lib/web/libweb.dylib")

(define init&bind
  (foreign-procedure "do_init_and_bind" (string string)
		     ssize_t))
(define handle-connection
  (foreign-procedure "handle_connection"
		       (ssize_t void*) void))
(define web-loop
  (foreign-procedure __collect_safe "web_loop"
		     (ssize_t void*) void))
(define handle-connection-callback
  (lambda (p)
    (let ([code (foreign-callable __collect_safe p (ssize_t u8*) void)])
      (lock-object code)
      (foreign-callable-entry-point code))))

;;; Get `type` pointer
(define-syntax get-pointer-in-type
  (syntax-rules ()
    [(_ t)
     (foreign-procedure "get_pointer"
			(t) void*)]))
;;; C socket's send function
(define send
  (foreign-procedure "send"
		     (int void* size_t int)
		     ssize_t))
