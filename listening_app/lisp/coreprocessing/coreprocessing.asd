;;;; coreprocessing.asd

(asdf:defsystem #:coreprocessing
  :description "Describe coreprocessing here"
  :author "Your Name <your.name@example.com>"
  :license  "Specify license here"
  :version "0.0.1"
  :serial t
  :depends-on (#:cl-csv
	       #:jonathan)
  :components ((:file "package")
               (:file "database")
               (:file "coreprocessing")))


