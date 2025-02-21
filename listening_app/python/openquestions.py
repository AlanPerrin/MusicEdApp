#!/usr/bin/env python3
import sys
import startlisp as CL

def main():
    if len(sys.argv) < 2:
        print("Usage: openquestions.py \"your input text\" [--dev]")
        sys.exit(1)

    # Initialize Lisp and get the Lisp instance.
    lisp = CL.initialize_lisp()

    # Retrieve the Lisp function.
    get_note_questions = lisp.function("string-questions")  # More descriptive name



    try:
        # Call the Lisp function and handle potential errors
        
        questions = get_note_questions(1)
        #questions = hello()
        print("Note Questions:")
        print(questions)
        print("\n")
        print("Type:", type(questions))
    except Exception as e:
        print(f"Error calling Lisp function: {e}")
        sys.exit(1)

if __name__ == '__main__':
    main()