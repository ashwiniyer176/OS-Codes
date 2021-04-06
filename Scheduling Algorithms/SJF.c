#include <stdio.h>

int main()
{
	int numberOfJobs, job[15], burstTime[15], waitingTime[15], turnAroundTime[15], i, j, temp;
	float waitingTimeSum = 0, turnAroundTimeSum = 0;
	printf("\nEnter number of jobs: ");
	scanf("%d", &numberOfJobs);
	for (i = 0; i < numberOfJobs; ++i)
	{
		printf("\nEnter Burst Time for Job %d: ", i + 1);
		scanf("%d", &burstTime[i]);
		job[i] = i + 1;
	}
	for (i = 0; i < numberOfJobs; ++i)
	{
		for (j = 0; j < numberOfJobs - i - 1; ++j)
		{
			if (burstTime[j] > burstTime[j + 1])
			{
				temp = burstTime[j];
				burstTime[j] = burstTime[j + 1];
				burstTime[j + 1] = temp;

				temp = job[j];
				job[j] = job[j + 1];
				job[j + 1] = temp;
			}
		}
	}
	printf("\nJob\tBT\tWT\tTT");
	for (i = 0; i < numberOfJobs; ++i)
	{
		if (i == 0)
			waitingTime[i] = 0;

		else
		{
			waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
		}
		turnAroundTime[i] = burstTime[i] + waitingTime[i];
		waitingTimeSum += waitingTime[i];
		turnAroundTimeSum += turnAroundTime[i];
		printf("\n%d\t%d\t%d\t%d", job[i], burstTime[i], waitingTime[i], turnAroundTime[i]);
	}
	printf("\nAverage Waiting Time: %.2f\nAverage Turnaround Time:%.2f", waitingTimeSum / numberOfJobs, turnAroundTimeSum / numberOfJobs);
}
