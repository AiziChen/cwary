(load "tools.ss")
(load "default-settings.ss")
(load "lib/mysql/mysql.ss")
(load "lib/web/web.ss")

(define run-server
  (lambda (servhost servport)
    (let ([socket-listen (init&bind servhost servport)])
      (check 'init&bind socket-listen)
      (web-loop socket-listen cb1))))

;;; Alias
(define @server run-server)



