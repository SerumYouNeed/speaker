#include <stdio.h>

void add1(int a)
{
    a++;
}


int main(void)
{
    char *str = "this is from char *";
    char str2[] = "this is from char array";

    printf("%s\n", str);
    printf("%s\n", str2);

    int a = 10;
    int *p;
    
    printf("a: %zu\n", sizeof a);
    printf("p: %zu\n", sizeof p);
    printf("*p: %zu\n", sizeof *p);
    
    return (0);
}