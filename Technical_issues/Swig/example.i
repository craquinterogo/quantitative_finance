/* File: Example.i */
%module example

%{
#define SWIG_FILE_WITH_INIT
#include "example.h"
%}

unsigned long long int fact(int n);