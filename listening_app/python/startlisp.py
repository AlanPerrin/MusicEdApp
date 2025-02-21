#!/usr/bin/env python3
import os
import sys
import cl4py

def initialize_lisp():
    # Create a Lisp interpreter instance.
    lisp = cl4py.Lisp()
    # Get the Lisp 'load' function.
    load = lisp.function('load')
    
    base_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
    
    # Load Quicklisp
    quicklisp_path = r'C:\Users\guita\OneDrive\Documents\Emacs\quicklisp\setup.lisp'
    try:
        load(quicklisp_path)
        print(f"Quicklisp loaded from {quicklisp_path}")
    except Exception as e:
        print(f"Error loading Quicklisp: {e}")
        sys.exit(1)
    
    # Construct the path to your ASDF system definition file.
    system_path = os.path.join(base_dir, "lisp", "coreprocessing", "coreprocessing.asd")
    fasl_path = os.path.join(base_dir, "lisp", "lm.fasl")
    
    force_source = "--dev" in sys.argv
    if force_source or not os.path.exists(fasl_path):
        print("Loading Lisp source file:", system_path)
        load(system_path)
        print(f"String-processing system ASD file loaded from {system_path}")
        ql = lisp.function("ql:quickload")
        ql("coreprocessing")
        print("String-processing package loaded")
    else:
        print("Loading compiled Lisp file:", fasl_path)
        load(fasl_path)
    
    return lisp  # Return the Lisp instance

if __name__ == '__main__':
    initialize_lisp()
