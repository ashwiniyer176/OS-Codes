#include <stdio.h>
#include <stdlib.h>
int size = 5;
int queue[5], head = 0, tail = 0, empty = -2;

void replace(int pageNumber, int index)
{
    queue[index] = pageNumber;
}

int checkPageHit(int pageNumber)
{
    for (int i = 0; i < size; ++i)
    {
        if (queue[i] == pageNumber)
            return 1;
    }
    return 0;
}

void chooseVictimAndReplace(int pageNumber)
{
    printf("\nHead:%d", head);
    if (head > 4)
    {
        head = 0;
        replace(pageNumber, head);
        ++head;
    }
    else
    {
        replace(pageNumber, head);
        ++head;
    }
}

int getFirstEmptyIndex()
{
    for (int i = 0; i < size; ++i)
    {
        if (queue[i] == empty)
            return i;
    }
    return -3;
}

void addToQueue(int pageNumber)
{
    int isReplaced = 0;
    int emptyIndex = getFirstEmptyIndex();
    if (emptyIndex > -1)
    {
        replace(pageNumber, emptyIndex);
        printf("\nEmpt Index: %d", emptyIndex);
        return;
    }
    else
        chooseVictimAndReplace(pageNumber);
}

void printQueue()
{
    printf("\nQueue:");
    for (int i = 0; i < size; ++i)
    {
        printf("%d, ", queue[i]);
    }
}
int main()
{
    int pageNumber;
    for (int i = 0; i < size; ++i)
        queue[i] = empty;
    while (1)
    {
        printf("\nEnter Page Number (-1 to exit):");
        scanf("%d", &pageNumber);
        if (pageNumber == -1)
            exit(1);
        if (checkPageHit(pageNumber) == 0)
            addToQueue(pageNumber);
        else
            printf("\nAlready in queue");
        printQueue();
    }
}