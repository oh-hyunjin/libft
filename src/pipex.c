/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:48:50 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/22 19:12:11 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_cmd(int current, int fds[])
{
	int		infile_fd;
	char	*arg[]={"cat", NULL};

	close(fds[0]);
	printf("first child prcoess start\n");
	infile_fd = open("infile", O_RDWR, 0644);
	if (infile_fd < 0)
		printf("open error\n");
	printf("outfile fd : %d\n", infile_fd);

	dup2(infile_fd, 0);
	dup2(fds[1], 1);
	execve("/bin/cat", arg, NULL);
}

void	last_cmd(int current, int fds[])
{
	int		outfile_fd;
	char	*arg[]={"cat", NULL};

	close(fds[1]);
	printf("last child prcoess start\n");
	outfile_fd = open("outfile", O_RDWR, 0644);
	if (outfile_fd < 0)
		printf("open error\n");
	printf("outfile fd : %d\n", outfile_fd);

	dup2(fds[0], 0);
	dup2(outfile_fd, 1);
	execve("/bin/cat", arg, NULL);
}

void	parent()
{
	int		wait_status;

	// while(wait(&wait_status) != -1);
	exit(0);
}

int main(int argc, char **argv)
{
	pid_t	pid;
	int		fds[2];
	int		current;

	current = 0;
	printf("start\n");
	if (pipe(fds) < 0)
	{
		printf("error\n");
		exit(0);
	}
	printf("fds : [%d] [%d]\n", fds[0], fds[1]);
	while (++current != 3)
	{
		pid = fork();
		if (pid < 0)
		{
			printf("error\n");
			exit(0);
		}
		else if (pid == 0)
			break ;
	}

	if (pid == 0 && current == 1)
		first_cmd(current, fds);
	else if (pid == 0 && current == 2)
		last_cmd(current, fds);
	else if (pid != 0)
		parent();
}