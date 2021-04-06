#include <stdio.h>
#include <string.h>

typedef struct Queue
{
    int jobSequence[10];
    int burstTime[10];
    int numberOfJobs;
} Q;

Q completedJobQueue;
int top = 0;
void printQueue(Q queue)
{
    for (int i = 0; i < queue.numberOfJobs; ++i)
    {
        printf("%d\t%d\n", queue.jobSequence[i], queue.burstTime[i]);
    }
}

void RoundRobin(Q *queue, Q *nextQueue, int timeQuantum)
{
    int k = 0;
    for (int i = 0; i < queue->numberOfJobs; ++i)
    {
        if (queue->burstTime[i] <= timeQuantum && queue->jobSequence[i] > 0)
        {
            queue->burstTime[i] = 0;
            printf("\nCompleted Process: %d in Round Robin", queue->jobSequence[i]);
            completedJobQueue.jobSequence[top] = queue->jobSequence[i];
            completedJobQueue.burstTime[top] = 0;
            ++top;
        }
        else
        {
            queue->burstTime[i] -= timeQuantum;
            nextQueue->jobSequence[k] = queue->jobSequence[i];
            nextQueue->burstTime[k] = queue->burstTime[i];
            ++k;
        }
    }
    nextQueue->numberOfJobs = k;
}

void pushToCompletedJobQueue(int jobID)
{
    completedJobQueue.jobSequence[top] = jobID;
    completedJobQueue.burstTime[top] = 0;
    ++top;
}
void FFCS(Q *queue)
{
    for (int i = 0; i < queue->numberOfJobs; ++i)
    {
        queue->burstTime[i] = 0;
        printf("\nCompleted Process: %d in FFCS", queue->jobSequence[i]);
        pushToCompletedJobQueue(queue->jobSequence[i]);
    }
}

void printJobSequence()
{
    printf("\nJobs Completed Are in order:\n");
    for (int i = 0; i < top; ++i)
    {
        printf("%d\t", completedJobQueue.jobSequence[i]);
    }
    printf("\n");
}

int main()
{
    Q roundRobinQ1, roundRobinQ2, FFCSQ, initialQ;
    printf("\nEnter total number of jobs:");
    scanf("%d", &initialQ.numberOfJobs);
    for (int i = 0; i < initialQ.numberOfJobs; ++i)
    {
        printf("\nEnter Burst Time for Job %d:", i + 1);
        scanf("%d", &initialQ.burstTime[i]);
        initialQ.jobSequence[i] = i + 1;
    }
    printQueue(initialQ);
    RoundRobin(&initialQ, &roundRobinQ1, 4);
    RoundRobin(&roundRobinQ1, &roundRobinQ2, 8);
    FFCS(&roundRobinQ2);
    printJobSequence();

    return 0;
}