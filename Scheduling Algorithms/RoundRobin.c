#include <stdio.h>

void printArray(int arr[], int n)
{
	int i;
	printf("\n");
	for (i = 0; i < n; ++i)
	{
		printf("   %d", arr[i]);
	}
}
//Copy second array into the first
void copyArray(int arr1[], int arr2[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
	{
		arr1[i] = arr2[i];
	}
}

int findAverageOfArray(int arr[], int n)
{
	int i;
	float sum = 0;
	for (i = 0; i < n; ++i)
	{
		sum += arr[i];
	}

	return (sum);
}

void findTurnaroundTime(int waitingTime[], int burstTime[], int turnAroundTime[], int numberOfJobs)
{
	int i;
	for (i = 0; i < numberOfJobs; ++i)
	{
		turnAroundTime[i] = waitingTime[i] + burstTime[i];
	}
}

int roundRobin(int burstTime[], int timeQuantum, int numberOfJobs, int waitingTime[])
{
	int i, remainingBurstTime[20], time = 0, done;
	copyArray(remainingBurstTime, burstTime, numberOfJobs);
	while (1)
	{
		done = 1;
		for (i = 0; i < numberOfJobs; ++i)
		{

			if (remainingBurstTime[i] > 0)
			{
				done = 0;
				if (remainingBurstTime[i] > timeQuantum)
				{
					time += timeQuantum;
					remainingBurstTime[i] -= timeQuantum;
				}
				else
				{
					time = time + remainingBurstTime[i];
					waitingTime[i] = time - burstTime[i];
					remainingBurstTime[i] = 0;
				}
			}
		}
		if (done == 1)
			break;
	}
}

void printTable(int burstTime[], int timeQuantum, int numberOfJobs, int waitingTime[], int turnAroundTime[], int jobList[])
{
	int i;
	float avgWaitingTime, avgTurnaroundTime;
	findTurnaroundTime(waitingTime, burstTime, turnAroundTime, numberOfJobs);
	avgWaitingTime = findAverageOfArray(waitingTime, numberOfJobs);
	avgTurnaroundTime = findAverageOfArray(turnAroundTime, numberOfJobs);
	printf("\nJob\tWT\tBT\tTT");
	for (i = 0; i < numberOfJobs; ++i)
	{
		printf("\n%d\t%d\t%d\t%d", jobList[i], waitingTime[i], burstTime[i], turnAroundTime[i]);
	}
	printf("\n\nAverage Waiting time is: %.2f", avgWaitingTime / numberOfJobs);
	printf("\nAverage Turnaround time is: %.2f\n", avgTurnaroundTime / numberOfJobs);
}

int main()
{
	int i, numberOfJobs, jobList[20], burstTime[20], timeQuantum, waitingTime[20], turnaroundTime[20];
	printf("\nEnter number of jobs: ");
	scanf("%d", &numberOfJobs);
	for (i = 0; i < numberOfJobs; ++i)
	{
		printf("\nEnter Job %d Burst Time:", i + 1);
		scanf("%d", &burstTime[i]);
		jobList[i] = i + 1;
		waitingTime[i] = 0;
		turnaroundTime[i] = 0;
	}
	printf("\nEnter Time Quantum:");
	scanf("%d", &timeQuantum);
	roundRobin(burstTime, timeQuantum, numberOfJobs, waitingTime);
	printTable(burstTime, timeQuantum, numberOfJobs, waitingTime, turnaroundTime, jobList);
}
