#include <stdio.h>
#include <unistd.h>

int main()
{
	int		fd[2];
	char	buffer[30];

	pipe(fd);
	dup2(fd[1], 2);
	perror("Error!");

	read(fd[0], buffer, 30);
	printf("%s", buffer);
}