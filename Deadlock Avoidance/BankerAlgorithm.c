#include <stdio.h>

int allocation[10][5], jobSequence[10], k = 0, maximumRequired[10][5], currentNeed[10][5], totalResources[5], numberOfJobs, numberOfResources, allocatedResources[5], availableResources[5];

void print2DArray(int arr[][5])
{
    int i, j;
    printf("\n");
    for (i = 0; i < numberOfJobs; ++i)
    {
        for (j = 0; j < numberOfResources; ++j)
        {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
}

void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("\t%d", arr[i]);
    }
}

void getResources(int arr[][5], int n, int index, int max)
{
    int j;
    for (j = 0; j < n; ++j)
    {
        if (max == 0)
        {
            printf("\nEnter resource %d for P%d: ", j + 1, index);
            scanf("%d", &allocation[index][j]);
        }
        else
        {
            printf("\nEnter maximum resource %d for P%d: ", j + 1, index);
            scanf("%d", &maximumRequired[index][j]);
        }
    }
}

void getAllocated()
{
    int i, j;
    for (i = 0; i < numberOfResources; ++i)
    {
        allocatedResources[i] = 0;
        for (j = 0; j < numberOfJobs; ++j)
        {
            allocatedResources[i] += allocation[j][i];
        }
    }
}

void getCurrentNeed()
{
    int i, j;
    for (i = 0; i < numberOfJobs; ++i)
    {
        for (j = 0; j < numberOfResources; ++j)
        {
            currentNeed[i][j] = maximumRequired[i][j] - allocation[i][j];
        }
    }
}

void getAvailableResources()
{
    for (int i = 0; i < numberOfResources; ++i)
    {
        availableResources[i] = totalResources[i] - allocatedResources[i];
    }
}

int canBeAllocated(int need[], int available[])
{
    int flag = 0;
    for (int x = 0; x < numberOfResources; ++x)
    {
        if (need[x] != 0)
        {
            flag = 1;
            break;
        }
    }
    for (int i = 0; i < numberOfResources; ++i)
    {
        if (available[i] < need[i])
        {
            flag = 0;
            break;
        }
    }
    return flag;
}

void addToJobSequence(int jobID)
{
    jobSequence[k] = jobID;
    ++k;
}

void getSequence()
{
    for (int i = 0; i < numberOfJobs; ++i)

    {
        if (canBeAllocated(currentNeed[i], availableResources) == 1)
        {
            addToJobSequence(i);
            for (int j = 0; j < numberOfResources; ++j)
            {
                availableResources[j] += currentNeed[i][j];
                currentNeed[i][j] = 0;
                allocation[i][j] = 0;
                maximumRequired[i][j] = 0;
            }
        }
    }
}

int jobsAreNotDone()
{
    if (k < numberOfJobs)
        return 1;
    return 0;
}

void BankersAlgorithm()
{
    printf("\nBankers Algorithm");
    while (jobsAreNotDone() == 1)
    {
        getAllocated();
        getCurrentNeed();
        getAvailableResources();
        getSequence();
        print2DArray(currentNeed);
    }
    printArray(jobSequence, numberOfJobs);
}

int main()
{
    printf("Enter number of jobs: ");
    scanf("%d", &numberOfJobs);
    printf("\nEnter number of resources: ");
    scanf("%d", &numberOfResources);
    int i, j;
    for (i = 0; i < numberOfJobs; ++i)
    {
        getResources(allocation, numberOfResources, i, 0);
        getResources(maximumRequired, numberOfResources, i, 1);
    }
    printf("\nTotal Resources: ");
    for (i = 0; i < numberOfResources; ++i)
    {
        printf("\nEnter Max Resources for Resource %d: ", i);
        scanf("%d", &totalResources[i]);
    }
    printf("\nallocation: ");
    print2DArray(allocation);
    printf("\nMaximum Required:");
    print2DArray(maximumRequired);
    printf("\nTotal Resources: ");
    printArray(totalResources, numberOfResources);
    BankersAlgorithm();
}
