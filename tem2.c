#include <stdio.h>

int main (void)
{
    int a = 363;
    char *p = (char *)&a;

    printf("Value of a: %d\n", a);
    printf("Address of a: %p\n", p);
    printf("Address of next cell: %p\n", p + 1);

    printf("Address of char: %p\n", (char *)p);
    printf("Value of char: %d\n", *p);
    printf("Address of char + 1: %p\n", (char *)(p + 1));
    printf("Value of char + 1: %d\n", *(p + 1));
    return(0);
}