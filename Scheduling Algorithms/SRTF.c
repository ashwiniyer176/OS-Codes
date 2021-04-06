#include <stdio.h>
#include <unistd.h>

struct process
{
	int processNumber;
	int burstTime;
	int arrivalTime;
};

int main()
{

	struct process jobs[20];
	int waitingTime[20], turnAroundTime[20], complete[20], burstTime[20], execution[20 * 10];
	int n, i, elapsed, small = 0, totalwait = 0, averageWaitingTime = 0, averageTurnaroundTime = 0, count = 0, executionLength = 0;
	printf("Enter number of processes: ");
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		// Input Values and assign
		int x;
		printf("\nEnter burstTime time for %d: ", i + 1);
		scanf("%d", &x);
		jobs[i].burstTime = x;
		burstTime[i] = x;
		jobs[i].processNumber = i + 1;
		printf("Enter arrivalTime time of %d: ", i + 1);
		scanf("%d", &x);
		jobs[i].arrivalTime = x;
	}
	// Scheduling and running simulation
	jobs[20 - 1].burstTime = 999999;
	for (elapsed = 0; count != n; elapsed++)
	{
		small = 20 - 1;
		for (i = 0; i < n; i++)
		{
			if (jobs[i].arrivalTime <= elapsed && jobs[i].burstTime < jobs[small].burstTime && jobs[i].burstTime > 0)
				small = i;
		}
		jobs[small].burstTime--;
		execution[elapsed] = jobs[small].processNumber;
		executionLength++;

		if (jobs[small].burstTime == 0)
		{
			count++;
			complete[small] = elapsed + 1;
			waitingTime[small] = elapsed - jobs[small].arrivalTime - burstTime[small] + 1;
			turnAroundTime[small] = elapsed - jobs[small].arrivalTime + 1;
		}
	}

	printf("\n\n\n Job\tBT\tAT\tWT\tTT\n");
	for (i = 0; i < n; i++)
	{
		averageWaitingTime += waitingTime[i];
		averageTurnaroundTime += turnAroundTime[i];
		// Printing Values
		printf("%d\t%d\t%d\t%d\t%d\n", jobs[i].processNumber, burstTime[i], jobs[i].arrivalTime, waitingTime[i], turnAroundTime[i]);
	}

	printf("\n\nAverage Waiting time is: %d", averageWaitingTime / n);
	printf("\nAverage Turnaround time is: %d\n", averageTurnaroundTime / n);
	return 0;
}