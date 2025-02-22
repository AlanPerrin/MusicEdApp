#!/usr/bin/env python3
import sys
import startlisp as CL

def main():
    # Parse input from command-line arguments.
    if len(sys.argv) < 2:
        print("Usage: python_bridge.py \"your input text\" [--dev]")
        sys.exit(1)
    # The first argument is the input text.
    input_text = sys.argv[1]
    # Initialize Lisp and load your Lisp code.
    lisp = CL.initialize_lisp()
    #Common Lisp function called
    html_out = lisp.function("coreprocessing::html-out")
    html_out(input_text)
    
if __name__ == '__main__':
    main()
