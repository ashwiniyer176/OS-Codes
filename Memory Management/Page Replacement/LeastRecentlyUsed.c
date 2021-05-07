#include <stdio.h>

int queue[15], size, empty = -2, LRU[15], top = -1;

int checkPageHit(int pageNumber)
{
    for (int i = 0; i < size; ++i)
    {
        if (queue[i] == pageNumber)
            return 1;
    }
    return 0;
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

int LRUPop(int index)
{
    int poppedElement = LRU[index];
    for (int i = index; i < top; ++i)
    {
        LRU[i] = LRU[i + 1];
    }
    --top;
    return poppedElement;
}

void replaceMissingPage(int pageNumber)
{
    int nextIndexQueue[5], emptyIndex = getFirstEmptyIndex();
    if (emptyIndex > -1)
    {
        queue[emptyIndex] = pageNumber;
        LRU[++top] = pageNumber;
        return;
    }
    else
    {
        int victimPageNumber = LRUPop(0);
        for (int i = 0; i < size; ++i)
        {
            if (queue[i] == victimPageNumber)
            {
                queue[i] = pageNumber;
                LRU[++top] = pageNumber;
            }
        }
    }
}

void searchAndPopFromLRU(int key)
{
    int i;
    for (i = 0; i < top; ++i)
    {
        if (LRU[i] == key)
            break;
    }
    LRUPop(i);
    LRU[++top] = key;
}

void addToQueue(int pageNumber)
{

    if (checkPageHit(pageNumber) == 1)
    {
        printf("\nAlready in queue. Updating position");
        searchAndPopFromLRU(pageNumber);
    }

    else
    {
        replaceMissingPage(pageNumber);
    }
}

void printArray(int array[], int n)
{
    printf("\nArray:");
    for (int i = 0; i < n; ++i)
    {
        printf("%d, ", array[i]);
    }
}

int main()
{
    int pageNumber = 0;
    printf("\nEnter size of queue: ");
    scanf("%d", &size);
    for (int i = 0; i < size; ++i)
        queue[i] = empty;
    while (1)
    {
        printf("\nEnter page number: ");
        scanf("%d", &pageNumber);
        if (pageNumber == -1)
            break;
        addToQueue(pageNumber);
        printArray(queue, size);
    }
    return 0;
}