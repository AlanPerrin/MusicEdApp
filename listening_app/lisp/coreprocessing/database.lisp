;;;; coreprocessing.lisp

(in-package #:coreprocessing)


(defparameter *note-csv-filename* (parse-namestring "Questions/Note_Questions/Note_Questions.csv"))
(defparameter *pathname*
  (let ((pathname (uiop:getcwd)))
    (dotimes (i 1 pathname)
      (setf pathname (uiop:pathname-parent-directory-pathname pathname)))))
(defparameter *NotePath* (uiop:merge-pathnames* *note-csv-filename* *pathname*))

(defun load-note-questions (level)
  "Loads note questions from the CSV file based on the given level.
Returns a list of lists representing the questions."
  (with-open-file (stream *NotePath* :direction :input)
    (let* ((csv-data (cl-csv:read-csv stream))
           (headers (mapcar #'string-downcase (first csv-data)))
           (rows (rest csv-data))
           (question-lists
            (mapcar (lambda (row)
                      (loop for h in headers
                            for val in row
                            collect (list h (substitute #\/ #\\ val))))
                    rows)))
      (cond ((= level 1)
             (remove-if-not (lambda (row)
                              (string= (second (assoc "difficulty" row :test #'string=)) "1"))
                            question-lists))
            ((= level 2)
             (remove-if (lambda (row)
                          (string= (second (assoc "difficulty" row :test #'string=)) "3"))
                        question-lists))
            (t question-lists)))))


(defun string-questions (level)
  (format nil "~a"  (load-note-questions level)))

(defun notes-json (level)
  (jonathan:to-json (load-note-questions level)))
