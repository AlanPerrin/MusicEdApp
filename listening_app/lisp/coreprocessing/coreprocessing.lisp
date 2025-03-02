;;;; coreprocessing.lisp

(in-package #:coreprocessing)

(defun language-model-response (input)
  (format nil "Language Model Response: You entered '~a'" input))

(defun generate-html-string (text)
  "Generate an HTML string with a custom doctype and pretty-printing.
The TEXT argument is inserted into the <p> tag."
  (format nil
"<!DOCTYPE html>
<html>
  <head>
    <meta charset=\"UTF-8\" />
    <title>Generated HTML</title>
  </head>
  <body>
    <h1>Your Output</h1>
    <p>~A</p>
  </body>
</html>" text))

(defun save-html-to-file (filename html-string)
  "Save HTML-STRING to the file named FILENAME."
  (with-open-file (stream filename
                            :direction :output
                            :if-exists :supersede
                            :if-does-not-exist :create)
    (write-string html-string stream)))


(defun html-out (input)
  (save-html-to-file "output.html" (generate-html-string (language-model-response input))))
