#!/usr/bin/env python3
import sys
import ast
import json
import startlisp as CL

def parse_lisp_data(lisp_string):
    """Parses Lisp-style data into a Python list of lists."""
    try:
        # Use ast.literal_eval for safe evaluation of Lisp structure
        data = ast.literal_eval(lisp_string)
        return data
    except (SyntaxError, ValueError) as e:
        print(f"Error parsing Lisp data: {e}", file=sys.stderr)  # Print to stderr for C++ to capture
        return None

def main():
    # Parse input from command-line arguments.
    if len(sys.argv) < 2:
        print("Usage: python_bridge.py \"your input text\" [--dev]")
        sys.exit(1)
    # The first argument is the input text.
    input_text = sys.argv[1]
    # Initialize Lisp and load your Lisp code.
    lisp = CL.initialize_lisp()
    # Retrieve the Lisp function.
    get_note_questions = lisp.function("coreprocessing::notes-json")  # More descriptive name  
    try:
        # Call the Lisp function and handle potential errors   
        questions = get_note_questions(int( input_text))
        data = ast.literal_eval(questions)
        
        #extracting data
        answer = data[1][1][1]
        svg= data[1][0][1]
        sound = f"{data[1][2][1]}.mp3"

        result = {
            "answer": answer,
            "svg": svg,
            "sound": sound
        }
        json_string = json.dumps(result)

    except Exception as e:
        print(f"Error calling Lisp function: {e}")
        sys.exit(1)

if __name__ == '__main__':
    main()