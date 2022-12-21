#include <unistd.h>
#include <stdio.h>

int main()
{
	int		fd1[2];
	int		fd2[2];
	char	buffer[5000];
	pid_t	pid;

	if (pipe(fd1) == -1 || pipe(fd2) == -1)
	{
		printf("pipe error\n");
		return (1);
	}

	pid = fork();
	if (pid == -1)
	{
		printf("fork error\n");
		return (1);
	}
	else if (!pid)
	{
		write(fd1[1], "(자식에서 입력)\n", 25);
		read(fd2[0], buffer, 25);
		printf("\n자식 출력: %s\n", buffer);
	}
	else
	{
		write(fd2[1], "(부모에서 입력)", 25);
		read(fd1[0], buffer, 5000);
		printf("\n부모 출력: %s\n", buffer);
	}
}