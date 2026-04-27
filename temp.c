#include <stdio.h>



int main(void)
{
    FILE *fp;

    fp = fopen("list.txt", "w");
    char task[1024];
    int taskNumber = 1;

    printf("Enter new task: \n");
    scanf(" %s", task);
    fprintf(fp, "%d. %s", taskNumber, task);

}