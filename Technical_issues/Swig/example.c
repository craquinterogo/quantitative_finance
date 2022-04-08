/* File: example.c */

#include "example.h"

unsigned long long int fact(int n) {
    if (n == 0) {
        return 1;
    }else {
        return n * fact(n - 1);
    }
    return 0;
}