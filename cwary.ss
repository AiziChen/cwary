(load "tools.ss")
(load "default-settings.ss")
(load "lib/mysql/mysql.ss")
(load "lib/web/web.ss")

(define run-server
  (case-lambda
    [(servhost servport)
     (let ([socket-listen (init&bind servhost servport)])
       (check 'init&bind socket-listen)
       (web-loop socket-listen cb1))]
    [(servport)
     (run-server (s-ref settings 'serv-address) servport)]))

(define service-add
  (lambda (paths serve-f)
    '()))

;;; Alias

(define @server run-server)



