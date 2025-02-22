#!/usr/bin/env python3
import sys
import startlisp as CL


def main():
    #if len(sys.argv) < 2:
    #    print("Usage: simplified_bridge.py \"your input text\"", file=sys.stderr)
    #    sys.exit(1)

   # input_text = sys.argv[1]
    #print(f"Received: {input_text}")  # Just print the input
    
    # Parse input from command-line arguments.
    if len(sys.argv) < 2:
        print("Usage: python_bridge.py \"your input text\" [--dev]")
        sys.exit(1)
    # The first argument is the input text.
    input_text = sys.argv[1]
    
    # Initialize Lisp and load your Lisp code.
    lisp = CL.initialize_lisp()

    #made better
    html_out = lisp.function("coreprocessing::html-out")
    result = html_out(input_text)
    print(result)

    # Retrieve all needed Lisp functions.
    #language_model_response = lisp.function("coreprocessing::language-model-response")
    #generate_html_string     = lisp.function("coreprocessing::generate-html-string")
    #save_html_to_file        = lisp.function("coreprocessing::save-html-to-file")


    # Call the Lisp functions in sequence:
    # 1. Get a response from the language model.
    #lisp_response = language_model_response(input_text)
    #print("Language model response:", lisp_response)

    # 2. Generate an HTML string using the response.
    #html_string = generate_html_string(lisp_response)
    #print("Generated HTML:", html_string)

    # 3. Save the HTML string to a file named "output.html".
    #save_html_to_file("output.html", html_string)
    #print("HTML saved to output.html")

if __name__ == '__main__':
    main()
