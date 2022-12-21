#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t	pid;
	pid_t	ret;
	int		status;

	pid = fork();
	if (pid == -1)
		return (1);
	else if (!pid)
	{
		printf("child 1 start\n");
		usleep(50000);
		printf("child 1 end\n");
		return (0);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return (1);
		else if (!pid)
		{
			printf("child 2 start\n");
			usleep(4900);
			printf("child 2 end\n");
		}
		else if (pid)
		{
			printf("parent start\n");
			ret = wait(&status);
			printf("parent end\n");
		}
	}
	return (0);
}