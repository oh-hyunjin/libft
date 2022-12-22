/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:47:25 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/22 16:14:55 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	pid_t	pid1, pid2;
	int		fds[2];
	int		fd_file1, fd_file2;
	char	buff[199];
	char	*envp[] = {0};

	if (pipe(fds))
		printf("error\n");
	pid1 = fork();

	if (pid1 < 0)
		printf("error\n");
	else if (pid1 == 0)
	{
		printf("first child\n");
		if ((fd_file1 = open("file1.txt", O_RDWR)) == -1)
			printf("open error\n");
		dup2(fds[1], 1);
		char *argg[]={"/bin/ls",NULL};
		execve("/bin/ls", argg, envp);
	}
	else
	{
		pid2 = fork();

		if (pid2 < 0)
			printf("error\n");
		else if (pid2 == 0)
		{
			printf("second child\n");
			if ((fd_file2 = open("file2.txt", O_RDWR)) == -1)
				printf("open error\n");
			dup2(fds[0], 0);
			dup2(fd_file2, 1);
			char *argg[]={"/usr/bin/grep","a", NULL};
			execve("/usr/bin/grep", argg, envp);
		}
		else
		{
			sleep(2);
			printf("end\n");
			exit(0);
		}
	}
}