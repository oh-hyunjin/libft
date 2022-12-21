#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t	pid;
	int		temp;

	temp = 10;
	pid = fork();
	if (pid == -1)
	{
		printf("fork fail");
		return (1);
	}
	else if (!pid)
	{
		printf("Child process before : %d\n", temp);
		temp+= 10;
		printf("Child process after : %d\n", temp);
	}
	else if (pid)
	{
		printf("Parent process before : %d\n",temp);
		temp += 20;
		printf("Parent process after : %d\n", temp);
	}
	return (0);
}