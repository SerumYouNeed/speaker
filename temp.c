#include <stdio.h>

int myStrLen(char *s)
{
    char *p=s;

    while (*p != '\0')
    {
        printf("*p: %c\n", *p);
        printf("p: %p\n", p);
        p++;
    }
    return (p-s);
}

int main(void)
{
    char *myStr = "hello!";
    printf("The length of the string is: %d\n", myStrLen(myStr));

    return (0);
}