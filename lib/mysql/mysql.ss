(load-shared-object "lib/mysql/libcmysql-ffi.dylib")

;;; create an connection then return it
(define mysql-connect
  (foreign-procedure "connect"
		     (string string string string int)
		     void*))
;;; close connection
(define mysql-close
  (foreign-procedure "mysql_close"
		     (void*)
		     void))
;;; return `lb_buff_t` type
(define mysql-query
  (foreign-procedure "query"
		     (void* string)
		     string))
;;; execute an sql
(define mysql-execute
  (foreign-procedure "affect_sql"
		     (void* string)
		     int))
;;; free the lb_buff_t
(define lb-free
  (foreign-procedure "lb_free"
		     (void*)
		     void))

;;; TEST
#|
(define mysql (mysql-connect "localhost" "root" "Quanyec-123" "test" 3306))

(define rs (mysql-query mysql "SELECT * FROM user"))
(display rs)
(mysql-execute mysql "delete from user")
(mysql-execute mysql "insert into user (name, age) value ('Quanyec', 26)")


(mysql-close mysql)

|#
