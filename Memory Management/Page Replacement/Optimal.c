#include <stdio.h>
#include <stdlib.h>
int size = 4;
int queue[5], reference[20], numberOfPageRequests, empty = -2;

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
int getFirstEmptyIndex()
{
    for (int i = 0; i < size; ++i)
    {
        if (queue[i] == empty)
            return i;
    }
    return -3;
}

int findLargestIndex(int arr[], int n)
{
    int large = 0, i;
    for (int i = 1; i < n; ++i)
    {
        if (arr[i] > arr[large])
            large = i;
    }
    return large;
}

int getNextOccurenceIndex(int pageNumber, int index)
{
    for (int i = index; i < numberOfPageRequests; ++i)
    {
        if (reference[i] == pageNumber)
            return i;
    }
    return -1;
}

void replaceMissingPage(int pageNumber, int index)
{
    int nextIndexQueue[5], emptyIndex = getFirstEmptyIndex();
    if (emptyIndex > -1)
    {
        replace(pageNumber, emptyIndex);
        return;
    }
    else
    {
        for (int i = 0; i < size; ++i)
        {
            nextIndexQueue[i] = getNextOccurenceIndex(queue[i], index);
            if (nextIndexQueue[i] < 0)
            {
                replace(pageNumber, i);
                return;
            }
        }
        int largestInQueue = findLargestIndex(queue, size);
        replace(pageNumber, largestInQueue);
    }
}

void addToQueue(int pageNumber, int index)
{

    if (checkPageHit(pageNumber) == 1)
        printf("\nAlready in queue");
    else
        replaceMissingPage(pageNumber, index);
}

void printArray(int array[], int n)
{
    printf("\nArray:");
    for (int i = 0; i < n; ++i)
    {
        printf("%d, ", array[i]);
    }
}
void traverseReferenceArray()
{
    for (int i = 0; i < numberOfPageRequests; ++i)
    {
        addToQueue(reference[i], i + 1);
        printArray(queue, size);
    }
}
int main()
{
    int pageNumber;
    for (int i = 0; i < size; ++i)
        queue[i] = empty;

    printf("\nEnter number of page requests:");
    scanf("%d", &numberOfPageRequests);
    for (int i = 0; i < numberOfPageRequests; ++i)
    {
        printf("\nEnter page number:");
        scanf("%d", &reference[i]);
    }
    printArray(reference, numberOfPageRequests);
    traverseReferenceArray(numberOfPageRequests);
    printArray(queue, size);
}