#include <stdio.h>
#include <unistd.h>

struct process
{
    int processNumber;
    int burstTime;
    int priority;
};

int main()
{
    struct process job[10];
    int waitingTime[10], turnAroundTime[10];
    int numberofJobs, i;
    float waitingTimeSum = 0, avgWaitingTime = 0, avgTurnAroundTime = 0;
    printf("Enter number of processes: ");
    scanf("%d", &numberofJobs);
    for (i = 0; i < numberofJobs; i++)
    {
        int x;
        printf("\nEnter burstTime time for P%d: ", i + 1);
        scanf("%d", &x);
        job[i].burstTime = x;
        job[i].processNumber = i + 1;
        printf("Enter priority time of P%d: ", i + 1);
        scanf("%d", &x);
        job[i].priority = x;
    }

    for (i = 0; i < numberofJobs; i++)
    {
        int j, min = i;
        for (j = i; j < numberofJobs; j++)
        {
            if (job[j].priority < job[min].priority)
                min = j;
        }
        struct process temp = job[min];
        job[min] = job[i];
        job[i] = temp;
    }

    for (i = 0; i < numberofJobs; i++)
    {
        waitingTime[i] = waitingTimeSum;
        turnAroundTime[i] = waitingTime[i] + job[i].burstTime;
        waitingTimeSum += job[i].burstTime;
        avgWaitingTime += waitingTime[i];
        avgTurnAroundTime += turnAroundTime[i];
    }

    printf("\n\n Job\tBurst\tWait\tPriority\tTurnaround\n");
    for (i = 0; i < numberofJobs; i++)
    {
        printf(" %d\t%d\t%d\t%d\t\t%d\n", job[i].processNumber, job[i].burstTime, waitingTime[i], job[i].priority, turnAroundTime[i]);
    }

    printf("\n\nAverage Waiting time is: %.2f", avgWaitingTime / numberofJobs);
    printf("\nAverage Turnaround time is: %.2f\n", avgTurnAroundTime / numberofJobs);
    return 0;
}