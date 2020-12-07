(load "cwary.ss")

;; Connecting to the mysql server
;(define mysql (mysql-connect "localhost" "root" "Quanyec-123" "test" 3306))
;(check 'mysql-connection mysql)

;; Server Listen on: localhost: 8080
(@server "8080")


; close the resources ;
;; close the mysql server connection
;(mysql-close mysql)

