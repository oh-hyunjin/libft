#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int		temp;
	int		dup_fd;
	int		dup_read;
	char	buffer[5000];

	temp = open("test.txt", O_RDONLY);
	dup_fd = dup(temp);
	close(temp);
	if (dup_fd == -1)
		return(1);
	dup_read = read(dup_fd, buffer, 5000);
	close(dup_fd);
	if (dup_read == -1)
		return (1);
	buffer[dup_read] = '\0';
	write(STDOUT_FILENO, buffer, strlen(buffer));
	return (0);
}