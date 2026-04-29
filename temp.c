#include <stdio.h>
#include <string.h>
#include "menu.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <list_name>\n", argv[0]);
        return 1;
    }

    char listName[101];
    strcpy(listName, argv[1]);
    strcat(listName, ".txt");
    printMenu();
    int task = selectTask(task);
    switch (task)
    {    
        case 1: addTask(listName, lineCounter(listName));
                break;
        case 2: // deleteTask(listName);
                break;
        case 3: // markComplete(listName);
                break;
        case 4: // printList(listName);
                break;
        default: printf("Invalid option.\n");
    }
    
    return (0);
}