#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void convert_to_leet(FILE *f)
{
    int c;
    while ((c = fgetc(f)) != EOF) 
    {
        double p = rand() / (RAND_MAX + 1.0);
        if (isalpha(c)) 
        {
            if (p < 0.5 && (c == 'i' || c == 'I')) c = '1';
            if (p < 0.5 && (c == 'o' || c == 'O')) c = '0';
            if (p < 0.5 && (c == 'a' || c == 'A')) c = '4';
            if (p < 0.5 && (c == 'e' || c == 'E')) c = '3';
            if (p < 0.5 && (c == 's' || c == 'S')) c = '5';

            if (p < 0.5 && islower(c)) c = toupper(c);
            else if (p < 0.5 && isupper(c)) c = tolower(c);
        } 
        printf("%c", c);
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    if (argc > 1) 
    {
        int i = 1;
        while (i < argc) 
        {
            FILE *f = fopen(argv[i], "r");
            if (!f) 
            {
                fprintf(stderr, "l33t: %s: %s\n", argv[i], strerror(errno));
            } 
            else 
            {
                convert_to_leet(f);
            }
            fclose(f);
            i++;
        }
    }
    else 
    {
        convert_to_leet(stdin);
    }

    return 0;
}
