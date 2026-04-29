#include <stdio.h>

void printMenu(void)
{
    printf("********************\n");
    printf("|      OPTIONS     |\n");
    printf("********************\n");
    printf("1. Add task.\n");
    printf("2. Delete task.\n");
    printf("3. Mark as complete.\n");
    printf("4. Print list.\n\n");
}

int selectTask(int a)
{
    printf("********************\n");
    printf("|  Select a task:  |\n");
    printf("********************\n");
    scanf(" %d", &a);
    return a;
}

void addTask(char *s, int taskCounter)
{
    FILE *fp;
    fp = fopen(s, "a+");
    if (fp)
    {
        printf("Enter new task: \n");
        char task[1024];
        getchar(); // Consume the newline character left by scanf
        fgets(task, 1022, stdin);
        fprintf(fp, "%d. %s", taskCounter, task);
        fclose(fp);
    }
    else
    {
        printf("Error opening file.\n");
    }
}

int lineCounter(char *s)
{
    int linecount = 0;
    char buffer[1024];
    FILE *fp;
    fp = fopen(s, "r");
    if (fp == NULL)
    {
        return 1; // If the file doesn't exist, we start with 1 task
    }
    while (fgets(buffer, sizeof buffer, fp) != NULL) 
    {
        linecount++;
    }
    fclose(fp);
    return linecount;
}