#include <unistd.h>
#include <stdio.h>

int main()
{
	int	fd1[2];
	int	fd2[2];
	int	fd3[2];

	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	printf("%d %d\n", fd1[0], fd1[1]);
	printf("%d %d\n", fd2[0], fd2[1]);
	printf("%d %d\n", fd3[0], fd3[1]);
}