#include <iostream>
#include <string>
#include <stdio.h>      /* printf */
#include <string.h>     /* strcat */
#include <stdlib.h>     /* strtol */


using namespace std;

int main()
{
    // printf for different types:
    
    unsigned long long n;
    printf("%llu", n);
    
    unsigned long n;
    printf("%lu", n);   // unsigned long
    
    long n;
    printf("%ld", n);   // signed long

    long long int n;
    printf("%lld", n);   

    // %d is for signed int, 
    // %u is for unsigned int, 
    // %hh is for char instead of a wider type.)
    
    unsigned long long n;
    printf("0x%016llX", n); // "0x" followed by "0-padded", "16 char wide", "long long", "HEX with 0-9A-F"
    
    printf ("Val = %d(0x%X)\n", Val, Val);
    
    printf ("Characters: %c %c \n", 'a', 65);
    printf ("Decimals: %d %ld\n", 1977, 650000L);
    printf ("Preceding with blanks: %10d \n", 1977);
    printf ("Preceding with zeros: %010d \n", 1977);
    printf ("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
    printf ("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
    printf ("Width trick: %*d \n", 5, 10);
    printf ("%s \n", "A string");

    // printf binary:
    int i = 4;
    char buffer [33];
    itoa (i, buffer,2); // problem with itoa() function!
    printf ("binary: %s\n",buffer);
    
    {
        /* binary string to int */
        char *tmp;
        char *b = "0101";
        printf("%d\n", strtol(b, &tmp, 2));
    }

    {
        /* byte to binary string */
        printf("%s\n", byte_to_binary(5));
    }

    return 0;
}

const char *byte_to_binary(int x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

