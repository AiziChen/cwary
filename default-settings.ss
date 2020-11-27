;;; DEFAULT SETTINGS
(define settings
  `(*obj
    (app-version "0.1-dev")
    (http-version "HTTP/1.1")
    (response-extras-header
     ,(string-append "Server: cwary\r\n"
		     "Date: " (date-and-time) "\r\n"))))
