#include <stdio.h>
struct Job
{
    int jobID;
    int spaceRequired;
    int ffAllocated, bfAllocated, wfAllocated;
};
int numberOfJobs, numberOfSpaces;
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("\t%d", arr[i]);
    }
}
void printJobs(struct Job *jobPointer)
{
    printf("\nJob ID\tSpace");
    for (int i = 0; i < numberOfJobs; ++i)
    {
        printf("\n%d\t%d", jobPointer->jobID, jobPointer->spaceRequired);
        ++jobPointer;
    }
}

void getSpaces(int ffspaces[], int wfspaces[], int bfspaces[])
{
    printf("\nEnter number of Partitions:");
    scanf("%d", &numberOfSpaces);
    for (int i = 0; i < numberOfSpaces; ++i)
    {
        printf("\nEnter Space %d: ", i);
        scanf("%d", &ffspaces[i]);
        wfspaces[i] = ffspaces[i];
        bfspaces[i] = ffspaces[i];
    }
}

int getLargestSpaceIndex(int spaces[])
{
    int big = -1, bigIndex = -1;
    for (int i = 0; i < numberOfSpaces; ++i)
    {
        if (spaces[i] > big)
        {
            big = spaces[i];
            bigIndex = i;
        }
    }
    return bigIndex;
}

int getSmallestSpaceIndex(int spaces[], int spaceRequired)
{
    int small = __INT_MAX__, smallIndex = numberOfJobs;
    for (int i = 0; i < numberOfSpaces; ++i)
    {
        if (spaces[i] < small && spaces[i] >= spaceRequired)
        {
            small = spaces[i];
            smallIndex = i;
        }
    }
    return smallIndex;
}

void getExternalFragmentation(int internalFragmentedSpace)
{
    printf("\nLet's test for External Fragmentation");
    struct Job newJob;
    printf("\nJob Id: %d", numberOfJobs + 1);
    newJob.jobID = numberOfJobs + 1;
    printf("\nEnter Job Space Required:");
    scanf("%d", &newJob.spaceRequired);
    if (internalFragmentedSpace >= newJob.spaceRequired)
        printf("\n\nExternal Fragmentation! %d > %d", internalFragmentedSpace, newJob.spaceRequired);
    else
        printf("\n\nInsufficient Space");
}

void worstFit(int spaces[], struct Job *jobPointer)
{
    printf("\n\nApplying Worst Fit Algorithm on the data:");
    int index, sum = 0;
    for (int i = 0; i < numberOfJobs; ++i)
    {
        index = getLargestSpaceIndex(spaces);
        if (jobPointer->spaceRequired <= spaces[index])
        {
            printf("\nJob %d Allocated to Spaces[%d]=%d", jobPointer->jobID, index, spaces[index]);
            spaces[index] -= jobPointer->spaceRequired;
            sum += spaces[index];
            jobPointer->wfAllocated = 1;
        }
        ++jobPointer;
    }
    printf("\nInternal Fragmentation of Worst Fit: %d", sum);
    getExternalFragmentation(sum);
}

void bestFit(int spaces[], struct Job *jobPointer)
{
    printf("\n\nApplying Best Fit Algorithm on the given data:");
    int index, sum = 0;
    for (int i = 0; i < numberOfJobs; ++i)
    {
        index = getSmallestSpaceIndex(spaces, jobPointer->spaceRequired);
        if (jobPointer->spaceRequired <= spaces[index])
        {
            printf("\nJob %d Allocated to Spaces[%d]=%d", jobPointer->jobID, index, spaces[index]);
            spaces[index] -= jobPointer->spaceRequired;
            sum += spaces[index];
            jobPointer->bfAllocated = 1;
        }
        ++jobPointer;
    }
    printf("\nInternal Fragmentation of Best Fit:%d", sum);
    getExternalFragmentation(sum);
}

int returnFirstIndex(int spaces[], int spaceRequired)
{
    for (int i = 0; i < numberOfSpaces; ++i)
    {
        if (spaces[i] >= spaceRequired)
            return i;
    }
    return -1;
}

void firstFit(int spaces[], struct Job *jobPointer)
{
    printf("\n\nApplying First Fit Algorithm on the data");
    int sum = 0, index;
    for (int i = 0; i < numberOfJobs; ++i)
    {
        index = returnFirstIndex(spaces, jobPointer->spaceRequired);
        if (index > -1)
        {

            printf("\nJob %d Allocated to Spaces[%d]=%d", jobPointer->jobID, index, spaces[index]);
            spaces[index] -= jobPointer->spaceRequired;
            sum += spaces[index];
            jobPointer->ffAllocated = 1;
        }
        ++jobPointer;
    }
    printf("\nInternal Fragmentation of First Fit: %d", sum);
    getExternalFragmentation(sum);
}

int main()
{
    int i, ffspaces[20], bfspaces[20], wfspaces[20];
    struct Job jobs[15];
    printf("\nEnter number of jobs:");
    scanf("%d", &numberOfJobs);
    printf("Enter jobs:");
    for (i = 0; i < numberOfJobs; i++)
    {
        jobs[i].jobID = i + 1;
        printf("\nEnter Space:");
        scanf("%d", &jobs[i].spaceRequired);
        jobs[i].wfAllocated = 0;
        jobs[i].bfAllocated = 0;
        jobs[i].ffAllocated = 0;
    }
    printf("\nJob List:");
    printJobs(jobs);
    getSpaces(ffspaces, wfspaces, bfspaces);
    printArray(wfspaces, numberOfSpaces);
    worstFit(wfspaces, jobs);
    firstFit(ffspaces, jobs);
    bestFit(bfspaces, jobs);
    return 0;
}