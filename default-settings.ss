;;; DEFAULT SETTINGS
(define settings
  (sobj->hashtable
   `(*obj
     (app-version "0.1-dev")
     (serv-address "localhost")
     (http-version "HTTP/1.1")
     (response-extras-header
      ,(string-append "Server: cwary\r\n"
		      "Date: " (date-and-time) "\r\n")))))
