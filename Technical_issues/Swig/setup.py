#!/usr/bin/env python

"""
setup.py file for SWIG example
"""

from distutils.core import setup, Extension

example_module = Extension('_example', sources=['example_wrap.c','example.c'])

setup(
    name = 'example',
    version = '0.1',
    author = 'Cristian Q',
    ext_modules=[example_module],
    py_modules=['example']
)