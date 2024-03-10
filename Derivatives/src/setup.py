#!/usr/bin/env python

"""
setup.py file for SWIG example
"""

from distutils.core import setup, Extension

example_module = Extension('_Options', sources=['Options_wrap.cxx','Options.cpp'])

setup(
    name = 'Options',
    version = '0.1',
    author = 'Cristian Quintero',
    ext_modules=[example_module],
    py_modules=['Options']
)