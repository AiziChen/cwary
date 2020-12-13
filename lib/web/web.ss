(load "lib/web/libweb.ss")

;;; CONSTANTS
;;; String("\r\n\r\n") bytevector
(define DATA-SEPARATOR-LS '(13 10 13 10))
(define SEPARATOR "\r\n")
(define DATA-SEPARATOR (string-append SEPARATOR SEPARATOR))

;;; 
;;; TOOL FUNCTIONS
(define get-string-pointer (get-pointer-in-type string))

;;; 
;;; OTHER FUNCTIONS
(define generate-response-first-header
  (lambda (status-number)
    (let ([http-version (s-ref settings 'http-version)])
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
       SEPARATOR))))

(define generate-content-type
  (lambda (t)
    (string-append
     "Content-Type: "
     (case t
       ;; USE USUALLY
       [(.htm .html) "text/html"]	;HyperText Markup Language (HTML)
       [.js "text/javascript"]		;JavaScript
       [(.jpeg .jpg) "image/jpeg"]	;JPEG images
       [.png "image/png"]		;Portable Network Graphics
       [.svg "image/svg+xml"]		;Scalable Vector Graphics (SVG)
       [.gif "image/gif"]		;Graphics Interchange Format (GIF)
       [.json "application/json"]	;JSON format
       [.xml "application/xml"]		;XML
       [.sobj "application/sobj"]	;SObj format
       [.txt "text/plain"]		;Text, (generally ASCII or ISO 8859-n)
       [.xhtml "application/xhtml+xml"]	;XHTML
       ;; NORMAL CONTENT-TYPE
       [(form) "application/x-www-form-urlencoded"]
       [(image) "image/*"]
       [(audio) "audio/*"]
       [(video) "video/*"]
       [(font) "font/*"]
       [(all) "*/*"]
       ;; USE LESS
       [.aac "audio/aac"]		;AAC audio
       [.abw "application/x-abiword"]	;AbiWord document
       [.arc "application/x-freearc"]	;Archive document (multiple files embedded)
       [.avi "video/x-msvideo"]		;Archive document
       [.azw "application/vnd.amazon.ebook"] ;Amazon Kindle eBook format
       [.bin "application/octet-stream"]     ;Any kind of binary data
       [.bmp "image/bmp"]		;Windows OS/2 Bitmap Graphics
       [.bz "application/x-bzip"]	;BZip archive
       [.bz2 "application/x-bzip2"]	;BZip2 archiv
       [.csh "application/x-csh"]	;C-Shell script
       [.css "text/css"]		;Cascading Style Sheets (CSS)
       [.csv "text/csv"]		;Comma-separated values (CSV)
       [.doc "application/msword"]	;Microsoft Word
       [.docx "application/vnd.openxmlformats-officedocument.wordprocessingml.document"] ;Microsoft Word (OpenXML)
       [.eot "application/vnd.ms-fontobject"] ;MS Embedded OpenType fonts
       [.epub "application/epub+zip"]	;Electronic publication (EPUB)
       [.gz "application/gzip"]		;GZip Compressed Archive
       [.ico "image/vnd.microsoft.icon"] ;Icon format
       [.ics "text/calendar"]		;iCalendar format
       [.jar "application/java-archive"] ;Java Archive (JAR)
       [.jsonld "application/ld+json"]	;JSON-LD format
       [(.mid .midi) "audio/midi"] ;Musical Instrument Digital Interface (MIDI)
       [.mjs "text/javascript"]		;JavaScript module
       [.mp3 "audio/mpeg"]		;MP3 audio
       [.mpeg "video/mpeg"]		;MPEG Video
       [.mpkg "application/vnd.apple.installer+xml"] ;Apple Installer Package	
       [.odp "application/vnd.oasis.opendocument.presentation"]	;OpenDocument presentation document
       [.ods "application/vnd.oasis.opendocument.spreadsheet"] ;OpenDocument spreadsheet document
       [.odt "application/vnd.oasis.opendocument.text"]	;OpenDocument text document
       [.oga "audio/ogg"]		;OGG audio
       [.ogv "video/ogg"]		;OGG video
       [.ogx "application/ogg"]		;OGG
       [.opus "audio/opus"]		;Opus audio
       [.otf "font/otf"]		;OpenType font
       [.pdf "application/pdf"]		;Adobe Portable Document Format (PDF)
       [.php "application/x-httpd-php"]	;Hypertext Preprocessor (Personal Home Page)
       [.ppt "application/vnd.ms-powerpoint"] ;Microsoft PowerPoint
       [.pptx "application/vnd.openxmlformats-officedocument.presentationml.presentation"] ;Microsoft PowerPoint (OpenXML)
       [.rar "application/vnd.rar"]	;RAR archive
       [.rtf "application/rtf"]		;Rich Text Format (RTF)
       [.sh "application/x-sh"]		;Bourne shell script
       [.swf "application/x-shockwave-flash"] ;Small web format (SWF) or Adobe Flash document
       [.tar "application/x-tar"]	;Tape Archive (TAR)
       [(.tif .tiff) "image/tiff"]	;Tagged Image File Format (TIFF)
       [.ts "video/mp2t"]		;MPEG transport stream
       [.ttf "font/ttf"]		;TrueType Font
       [.vsd "application/vnd.visio"]	;Microsoft Visio
       [.wav "audio/wav"]		;Waveform Audio Format
       [.weba "audio/webm"]		;WEBM audio
       [.webm "video/webp"]		;WEBM video
       [.webp "image/webp"]		;WEBP image
       [.woff "font/woff"]		;Web Open Font Format (WOFF)
       [.woff2 "font/woff2"]		;Web Open Font Format (WOFF), Version 2
       [.xls "application/vnd.ms-excel"] ;Microsoft Excel	
       [.xlsx "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"] ;Microsoft Excel (OpenXML)
       [.xul "application/vnd.mozilla.xul+xml"]	;XUL
       [.zip "application/zip"]		;ZIP archive
       [.3gp "video/3gpp"]		;3GPP audio/video container
       [.3g2 "video/3gpp2"]		;3GPP2 audio/video container
       [.7z "application/x-7z-compressed"] ;7-zip archive
       [else "*/*"])
     SEPARATOR)))

(define generate-response-header
  (lambda (content-length)
    (string-append
     (generate-response-first-header 200)
     (s-ref settings 'response-extras-header)
     (generate-content-type '.txt)
     "Content-Length: " (number->string content-length)
     DATA-SEPARATOR)))

;;; Header Nevigation ;;;
;;; Data Split Collector
(define data-split&co
  (lambda (lat col sls)
    (cond
     [(null? lat) (col '() '())]
     [(starts-with lat sls)
      (col '() (list-tail lat (length sls)))]
     [else
      (data-split&co (cdr lat)
		  (lambda (l r)
		    (col (cons (car lat) l)
			 r))
		  sls)])))
;;; Payload Split
(define payload-split&co
  (lambda (lat col)
    (data-split&co lat col DATA-SEPARATOR-LS)))
;;; Header Line Split
(define line-split&co
  (lambda (lat col)
    (data-split&co lat col '(#\:))))
;;; Header split
(define get-next
  (lambda (lat sep col)
    (cond
     [(null? lat) '()]
     [(starts-with lat sep)
      (col (list-tail lat (length sep)))
      '()]
     [else
      (cons (car lat)
	    (get-next (cdr lat) sep col))])))
(define collect-line
  (lambda (lat sep)
    (cond
     [(null? lat) '()]
     [else
      (let ([nls '()])
	(cons (get-next lat sep
			(lambda (ls)
			  (set! nls ls)))
	      (collect-line nls sep)))])))
(define header&co->hashtable
  (case-lambda
    [(col) (header&co->hashtable col (make-eq-hashtable))]
    [(col ht)
     (for-each (lambda (line-ls)
		 (line-split&co line-ls
		  (lambda (key value)
		    (put-hash-table! ht (string->symbol (list->string key))
				     (list->string value)))))
	       col)
     ht]))


;;; BASE FUNCTIONS
(define cb1
  (handle-connection-callback
   (lambda (socket-client bv-data)
     (let-values ([(header-ht data)
		   (payload-split&co (bytevector->u8-list bv-data)
				     (lambda (header data)
				       (let* ([bv-header (u8-list->bytevector header)]
					      [headers (bytevector->string bv-header (native-transcoder))]
					      [header-downcase (string-downcase headers)]
					      [header-lines (collect-line (string->list header-downcase) '(#\return #\newline))]
					      [header-first-line (list->string (car header-lines))]
					      [header-ht (header&co->hashtable (cdr header-lines))]
					      [bv-data (u8-list->bytevector data)])
					 (values header-ht bv-data))))])
       (let* ([clen (s-ref header-ht 'content-length)]
	      [user-agent (s-ref header-ht 'user-agent)])
	 (let* ([content (if (null? user-agent) "Hello, World.." user-agent)]
		[clen (string-length content)]
		[response-header (generate-response-header clen)])
	   (c-write socket-client
		    (string->bytevector response-header (native-transcoder))
		    (string-length response-header))
	   (c-write socket-client
		    (string->bytevector content (native-transcoder))
		    clen))))))
  )
