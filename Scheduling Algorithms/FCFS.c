#include <stdio.h>

int main()
{
	int jobList[15], numberOfJobs, waitingTime[15], turnAroundTime[15];
	float waitingTimeSum = 0, turnAroundTimeSum = 0;
	int i, wait = 0;
	printf("\nEnter number of processes: ");
	scanf("%d", &numberOfJobs);
	for (i = 0; i < numberOfJobs; ++i)
	{
		printf("\nEnter Burst Time for Job %d: ", i + 1);
		scanf("%d", &jobList[i]);
	}
	wait = jobList[0];
	printf("\nJob\tWT\tBT\tTT");
	for (i = 0; i < numberOfJobs; ++i)
	{
		if (i == 0)
			waitingTime[i] = 0;

		else
		{
			waitingTime[i] = jobList[i - 1] + waitingTime[i - 1];
			waitingTimeSum += waitingTime[i];
		}
		turnAroundTime[i] = jobList[i] + waitingTime[i];
		turnAroundTimeSum += turnAroundTime[i];

		printf("\n%d\t%d\t%d\t%d", i + 1, waitingTime[i], jobList[i], turnAroundTime[i]);
	}
	printf("\nAverage Waiting Time: %.2f\nAverage Turnaround Time:%.2f", waitingTimeSum / numberOfJobs, turnAroundTimeSum / numberOfJobs);
	return 0;
}
