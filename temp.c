#include <stdio.h>

void add1(int a)
{
    a++;
}

struct car
{
    int year;
    int price;
    char *name;
};

void byref(struct car *c, int price)
{
    c->price = price;
}

int main(void)
{
    struct car mazda = {.year=2008, .name="mazda 6"};

    struct car *ptr = &mazda;
    
    printf("int: %zu\n", sizeof (int));
    printf("mazda: %zu\n", sizeof mazda);
    printf("mazda string: %zu\n", sizeof ptr->name);
    printf("amodel: %s\n", mazda.name);
    printf("year: %d\n", ptr->year);

    byref(ptr, 20000);

    printf("cena zmiana ptr: %d\n", ptr->price);
        
    return (0);
}