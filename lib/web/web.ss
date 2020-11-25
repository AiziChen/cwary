(load "lib/web/libweb.ss")

;;; BASE FUNCTIONS
(define run-server
  (lambda (servname servport)
    (let ([socket-listen (init&bind servname servport)])
      (web-loop socket-listen cb1))))

(define rsp-str
  (string-append
   "HTTP/1.1 200 OK\r\n"
   "Content-Type: text/plain\r\n"
   "Content-Length: 12\r\n\r\n"
   "hello, world"))

;;; String("\r\n\r\n") bytevector
(define sparator-bv (bytevector 13 10 13 10))

(define cb1
  (handle-connection-callback
   (lambda (socket-client bv-data)
     (send socket-client
	   (get-string-pointer rsp-str)
	   (string-length rsp-str)
	   0))))

;;; TOOL FUNCTIONS
(define get-string-pointer (get-pointer-in-type string))

;;; OTHER FUNCTIONS
(define response-first-header
  (lambda (status-number)
    (let ([http-version (sobj-ref settings 'http-version)])
      (string-append http-version " "
       (case status-number
	 [(200) "200 OK"]
	 [(301) "301 Moved Permanently"]
	 [(302) "302 Found"]
	 [(403) "403 Forbidden"]
	 [(404) "404 Not Found"]
	 [(500) "500 Internal Server Error"]
	 [(502) "502 Bad Gateway"]
	 [(504) "504 Gateway Timeout"]
	 [(100) "100 Continue"]
	 [(101) "101 Switching Protocals"]
	 [(201) "201 Created"]
	 [(202) "202 Accepted"]
	 [(203) "203 Non-authoritative Information"]
	 [(204) "204 No Content"]
	 [(205) "205 Reset Content"]
	 [(206) "206 Partial Content"]
	 [(300) "300 Multiple Choices"]
	 [(303) "303 See Other"]
	 [(304) "304 Not Modified"]
	 [(305) "305 Use Proxy"]
	 [(306) "306 Unused"]
	 [(307) "307 Temporary Redirect"]
	 [(400) "400 Bad Request"]
	 [(401) "401 Unauthorized"]
	 [(402) "402 Payment Required"]
	 [(405) "405 Method Not Allowed"]
	 [(406) "406 Not Acceptable"]
	 [(407) "407 Proxy Authentication Required"]
	 [(408) "408 Request Timeout"]
	 [(409) "409 Conflict"]
	 [(410) "410 Gone"]
	 [(411) "411 Length Required"]
	 [(412) "412 Precondition Failed"]
	 [(413) "413 Request Entity Too Large"]
	 [(414) "414 Request-url Too Long"]
	 [(415) "415 Unsupported Media Type"]
	 [(416) "416 Requested Range Not Satisfiable"]
	 [(417) "417 Expectation Failed"]
	 [(501) "501 Not Implemented"]
	 [(503) "503 Service Unavailable"]
	 [(505) "505 HTTP Version Not Supported"]
	 [else "404 Not Found"])
       "\r\n"))))

;;; DEFAULT SETTINGS
(define settings
  `(*obj
    (http-version "HTTP/1.1")
    (response-extras-header
     ,(string-append "Server: cwary\r\n"
		     "Date: 2020-10-22\r\n"))))
